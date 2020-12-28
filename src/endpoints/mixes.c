/*
    Copyright (c) 2020 Hugo Melder and openTIDAL contributors

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "../include/handles.h"
#include "../include/openTIDAL.h"
#include "../include/parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

openTIDAL_ContentContainer
openTIDAL_GetMixItems (openTIDAL_SessionContainer *session, const char *mixid)
{
    openTIDAL_ContentContainer o;
    openTIDAL_CurlContainer curl;

    openTIDAL_StructInit (&o);
    openTIDAL_StructAlloc (&o, 1);

    openTIDAL_StringHelper (&curl.endpoint, "/v1/mixes/%s/items", mixid);
    openTIDAL_StringHelper (&curl.parameter, "countryCode=%s", session->countryCode);
    if (!curl.endpoint || !curl.parameter) {
        o.status = -14;
        return o;
    }

    openTIDAL_CurlRequest (session, &curl, "GET", curl.endpoint, curl.parameter, NULL, 0, 0);
    if (curl.status != -1) {
        o.json = openTIDAL_cJSONParseHelper (curl.body);
        if (!o.json) {
            o.status = -14;
            return o;
        }

        if (curl.responseCode == 200) {
            cJSON *limit = NULL;
            cJSON *offset = NULL;
            cJSON *totalNumberOfItems = NULL;
            cJSON *items = NULL;
            cJSON *item = NULL;

            offset = cJSON_GetObjectItem ((cJSON *)o.json, "offset");
            limit = cJSON_GetObjectItem ((cJSON *)o.json, "limit");
            totalNumberOfItems = cJSON_GetObjectItem ((cJSON *)o.json, "totalNumberOfItems");
            items = cJSON_GetObjectItem ((cJSON *)o.json, "items");

            if (cJSON_IsArray (items)) {
                cJSON_ArrayForEach (item, items)
                {
                    openTIDAL_ItemsContainer Value;
                    cJSON *innerItem = NULL;

                    innerItem = cJSON_GetObjectItem (item, "item");

                    json_items_model processed_json = json_parse_items (innerItem);
                    parse_items_values (&Value, &processed_json);
                    parse_signed_number (limit, &Value.limit);
                    parse_signed_number (offset, &Value.offset);
                    parse_signed_number (totalNumberOfItems, &Value.totalNumberOfItems);

                    openTIDAL_StructAddItem (&o, Value);
                }
                o.status = 1;
            }
        }
        else {
            o.status = parse_status ((cJSON *)o.json, &curl, 0, mixid);
        }
    }
    openTIDAL_CurlRequestCleanup (&curl);
    return o;
}

openTIDAL_ContentContainer
openTIDAL_GetFavoriteMixes (openTIDAL_SessionContainer *session)
{
    openTIDAL_ContentContainer o;
    openTIDAL_CurlContainer curl;
    const char *endpoint = "/v1/pages/my_collection_my_mixes";

    openTIDAL_StructInit (&o);
    openTIDAL_StructAlloc (&o, 4);

    openTIDAL_StringHelper (&curl.parameter, "countryCode=%s&deviceType=BROWSER",
                            session->countryCode);
    if (!curl.parameter) {
        o.status = -14;
        return o;
    }

    openTIDAL_CurlRequest (session, &curl, "GET", endpoint, curl.parameter, NULL, 0, 0);
    if (curl.status != -1) {
        o.json = openTIDAL_cJSONParseHelper (curl.body);
        if (!o.json) {
            o.status = -14;
            return o;
        }

        if (curl.responseCode == 200) {
            cJSON *rows = NULL;
            cJSON *rowsArray = NULL;
            cJSON *modules = NULL;
            cJSON *modulesArray = NULL;
            cJSON *pagedList = NULL;
            cJSON *items = NULL;
            cJSON *item = NULL;

            rows = cJSON_GetObjectItem ((cJSON *)o.json, "rows");
            rowsArray = cJSON_GetArrayItem (rows, 0);
            modules = cJSON_GetObjectItem (rowsArray, "modules");
            modulesArray = cJSON_GetArrayItem (modules, 0);
            pagedList = cJSON_GetObjectItem (modulesArray, "pagedList");
            items = cJSON_GetObjectItem (pagedList, "items");

            if (cJSON_IsArray (items)) {
                cJSON_ArrayForEach (item, items)
                {
                    openTIDAL_MixContainer mix;

                    json_mix_model processed_json = json_parse_mix (item);
                    parse_mix_values (&mix, &processed_json);

                    openTIDAL_StructAddMix (&o, mix);
                }
                o.status = 1;
            }
        }
        else {
            o.status = parse_status ((cJSON *)o.json, &curl, session->userId, NULL);
        }
    }
    openTIDAL_CurlRequestCleanup (&curl);
    return o;
}

