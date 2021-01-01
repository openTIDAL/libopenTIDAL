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

#include "../external/cJSON.h"
#include "../http_connector.h"
#include "../openTIDAL.h"
#include "models.h"

#ifndef PARSE__h
#define PARSE__h

void *openTIDAL_cJSONParseHelper (char *input);

void parse_double (cJSON *object, double *number);
void parse_number (cJSON *object, size_t *number);
void parse_signed_number (cJSON *object, int *number);
void parse_bool (cJSON *object, int *number);
void parse_string (cJSON *object, char **string);

int parse_status (cJSON *input_json, openTIDAL_CurlContainer *Value, const size_t id,
                  const char *uuid);
int parse_raw_status (long *code);
int parse_unauthorized (cJSON *input_json, const size_t id);
int parse_notfound (cJSON *input_json, const size_t id, const char *uuid);
int parse_preconditionfailed (cJSON *input_json, const size_t id, const char *uuid);
int parse_badrequest (cJSON *input_json, const size_t id, const char *uuid);

/* parse Objects */
json_login_code_model json_parse_login_code (cJSON *directObject);
json_login_token_model json_parse_login_token (cJSON *directObject);
json_user_model json_parse_user (cJSON *directObject);
json_user_subscription_model json_parse_user_subscription (cJSON *directObject);
json_playlist_model json_parse_playlist (cJSON *directObject);
json_items_model json_parse_items (cJSON *directObject);
json_album_model json_parse_album (cJSON *directObject);
json_artist_model json_parse_artist (cJSON *directObject);
json_links_model json_parse_links (cJSON *directObject);
json_credit_model json_parse_credits (cJSON *directObject);
json_contributor_model json_parse_contributors (cJSON *directObject);
json_mix_model json_parse_mix (cJSON *directObject);
json_stream_model json_parse_stream (cJSON *directObject);
json_manifest_model json_parse_manifest (cJSON *directObject);

/* parse Values */
void parse_login_code_values (openTIDAL_LoginCodeContainer *code, json_login_code_model *json);

void parse_login_token_values (openTIDAL_LoginTokenContainer *token, json_login_token_model *json);

void parse_user_values (openTIDAL_UserContainer *user, json_user_model *json);

void parse_user_subscription_values (openTIDAL_UserSubscriptionContainer *sub,
                                     json_user_subscription_model *json);

void parse_playlist_values (openTIDAL_PlaylistContainer *playlist, json_playlist_model *json);

void parse_items_values (openTIDAL_ItemsContainer *items, json_items_model *json);

void parse_album_values (openTIDAL_AlbumContainer *album, json_album_model *json);

void parse_artist_values (openTIDAL_ArtistContainer *artist, json_artist_model *json);

void parse_link_values (openTIDAL_LinkContainer *link, json_links_model *json);

void parse_contributor_values (openTIDAL_ContributorContainer *contrib,
                               json_contributor_model *json);

void parse_mix_values (openTIDAL_MixContainer *mix, json_mix_model *json);

void parse_stream_values (openTIDAL_StreamContainer *stream, json_stream_model *json);

/* extra */
void parse_search (openTIDAL_ContentContainer *o, cJSON *input_json);
void parse_home (openTIDAL_ContentContainer *o, cJSON *input_json);

#endif