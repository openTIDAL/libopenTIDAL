#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cTidal.h"

playlist_model get_playlist(char *playlistid)
{
  char *endpoint = url_cat_str("playlists/", playlistid, "");
  char *baseparams = param_cat("100", "", "");
  curl_model req = curl_get(endpoint, baseparams);
  if (req.status != -1)
  {
    cJSON *input_json = json_parse(req.body);
    return parse_playlist(input_json, 0);
    /* always cleanup */
    cJSON_Delete(input_json);
  }
  else
  {
    printf("%s\n", "Request Error: cURL returned a 4xx status code. Authorization Error.");
    playlist_model Value;
    Value.status = -1;
    return Value;
  }
  /*Cleanup*/
  free(endpoint);
  free(baseparams);
  free(req.body);
}

items_model get_playlist_items(char *playlistid)
{
  char *endpoint = url_cat_str("playlists/", playlistid, "/items");
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

char *get_playlist_etag(char *playlistid)
{
  /* Request playlist endpoint to scrape eTag Header  */
  char *endpoint = url_cat_str("playlists/", playlistid, "");
  char *baseparams = param_cat("100", "", "");
  curl_model req = curl_head(endpoint, baseparams); /* Returns Header with eTag */
  int i = 0; /* Counter for Buffer (Header) Splitter  */
  int e; /* Counter for ETag-String Extraction  */
  char *p = strtok (req.header, "\n"); 
  char *array[30]; /* Buffer for splitted HTTP-Header  */
  char *eTag = malloc(20);
  while (p != NULL)
  {
    array[i++] = p;
    p = strtok (NULL, "\n"); /* Split if char is \n  */
  }
  for (e = 0; e < i; ++e)
  {
    if (strncmp(array[e], "ETag", 4) == 0) /* If String begins with ETag  */
    {
      int charCounter;
      int eTagCounter = 0;
      for (charCounter = 7; charCounter < strlen(array[e]); ++charCounter) /* Extract ETag Values */
      {
        if (array[e][charCounter] != '"')
        {
	  strcpy(&eTag[eTagCounter], &array[e][charCounter]);
	  eTagCounter = eTagCounter + 1;
        }
      }
      strcat(&eTag[eTagCounter + 1], "\0");
    }
  }
  /*Cleanup*/
  free(endpoint);
  free(baseparams);
  free(req.header);
  return eTag;  
}

int delete_playlist(char *playlistid)
{
  char buffer[80];
  snprintf(buffer, 80, "playlists/%s?countryCode=%s", playlistid, countryCode);

  curl_model req = curl_delete(buffer, "", "");
  if (req.status != -1)
  {
    return 1;
  }
  else
  {
    return -1;
  }
  /*Cleanup*/
  free(req.body);
}

int delete_playlist_item(char *playlistid, int index, char *eTag)
{
  char *eTagHeader = malloc(strlen(eTag)+16);
  strcpy(eTagHeader, "if-none-match: ");
  strcat(eTagHeader, eTag);
  char buffer[80];
  snprintf(buffer, 80, "playlists/%s/items/%d?countryCode=%s", playlistid, index, countryCode);
  curl_model req = curl_delete(buffer, "", eTagHeader);
  if (req.status != -1)
  {
    return 1;
  }
  else
  {
    return -1;
  }
  /*Cleanup*/
  free(eTagHeader);
  free(req.body);
}

int move_playlist_item(char *playlistid, int index, int toIndex, char *eTag)
{
  char *eTagHeader = malloc(strlen(eTag)+16);
  strcpy(eTagHeader, "if-none-match: ");
  strcat(eTagHeader, eTag);

  char buffer[80];
  snprintf(buffer, 80, "playlists/%s/items/%d?countryCode=%s", playlistid, index, countryCode);

  char bufferTwo[20];
  snprintf(bufferTwo, 20, "toIndex=%d", toIndex);
  curl_model req = curl_post(buffer, bufferTwo, eTagHeader);
  if (req.status != -1)
  {
    return 1;
  }
  else
  {
    return -1;
  }
  /*Cleanup*/
  free(eTagHeader);
  free(req.body);
}

int add_playlist_item(char *playlistid, size_t trackid, char *onDupes) /* onDupes = ADD or SKIP  */
{
  char buffer[80];
  snprintf(buffer, 80, "playlists/%s/items?countryCode=%s", playlistid, countryCode);

  char bufferTwo[60];
  snprintf(bufferTwo, 60, "trackIds=%zu&onDupes=%s&onArtifactNotFound=FAIL", trackid, onDupes);

  curl_model req = curl_post(buffer, bufferTwo, "");
  if (req.status != -1)
  {
    return 1;
  }
  else
  {
    return -1;
  }
  /*Cleanup*/
  free(req.body);
}

int add_playlist_items(char *playlistid, char *trackids, char *onDupes)
{
  char buffer[80];
  snprintf(buffer, 80, "playlists/%s/items?countryCode=%s", playlistid, countryCode);

  char bufferTwo[60];
  snprintf(bufferTwo, 60, "trackIds=%s&onDupes=%s&onArtifactNotFound=FAIL", trackids, onDupes);

  curl_model req = curl_post(buffer, bufferTwo, "");
  if (req.status != -1)
  {
    return 1;
  }
  else
  {
    return -1;
  }
  /*Cleanup*/
  free(req.body);
}
