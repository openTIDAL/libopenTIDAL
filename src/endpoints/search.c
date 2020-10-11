#include <stdio.h>
#include <stdlib.h>
#include "../include/cTidal.h"

/* Search */

search_model get_search(char *term, char *limit)
{
  char *encodedTerm = url_encode(term);
  char *endpoint = "search/";
  char *baseparams = param_cat(limit, encodedTerm, "");
  curl_model req = curl_get(endpoint, baseparams);
  if (req.status != -1)
  {
    cJSON *input_json = json_parse(req.body);
    return parse_search(input_json);
    /* always cleanup */
    cJSON_Delete(input_json);
  }
  else
  {
    printf("%s\n", "Request Error: cURL returned a 4xx status code. Authorization Error.");
    search_model Value;
    Value.status = -1;
    return Value;
  }
  /*Cleanup*/
  free(endpoint);
  free(baseparams);
  free(req.body);
  free(encodedTerm);
}
