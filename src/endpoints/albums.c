#include <stdio.h>
#include <stdlib.h>
#include "../include/cTidal.h"

album_model get_album(size_t albumid)
{
  char *endpoint = url_cat("albums/", albumid, "", 0);
  char *baseparams = param_cat("100", "", "");
  curl_model req = curl_get(endpoint, baseparams);
  if (req.status != -1)
  {
    cJSON *input_json = json_parse(req.body);
    return parse_album(input_json, 1);
    /* always cleanup */
    cJSON_Delete(input_json);
  }
  else
  {
    printf("%s\n", "Request Error: cURL returned a 4xx status code. Authorization Error.");
    album_model Value;
    Value.status = -1;
    return Value;
  }
  /*Cleanup*/
  free(endpoint);
  free(baseparams);
  free(req.body);
}

items_model get_album_items(size_t albumid)
{
  char *endpoint = url_cat("albums/", albumid, "/items", 0);
  char *baseparams = param_cat("100", "", "");
  curl_model req = curl_get(endpoint, baseparams);
  if (req.status != -1)
  {
    cJSON *input_json = json_parse(req.body);
    return parse_items(input_json, 2, 0);
    /* always cleanup */
    cJSON_Delete(input_json);
  }
  else
  {
    printf("%s\n", "Request Error: cURL returned a 4xx status code. Authorization Error.");
    items_model Value;
    Value.status = -1;
    return Value;
  }
  /*Cleanup*/
  free(endpoint);
  free(baseparams);
  free(req.body);
}
