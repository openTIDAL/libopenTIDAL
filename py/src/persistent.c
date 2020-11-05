#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "include/openTIDAL.h"

char *refresh_token;
char *access_token;
char *client_id = "8SEZWa4J1NVC5U5Y";
char *client_secret = "owUYDkxddz+9FpvGX24DlxECNtFEMBxipU0lBfrbq60=";
char *countryCode;
char *audioQuality;
char *videoQuality;
char *persistentFile;
size_t userId;
time_t expires_in;

char *json_stream;
int isStream = 0;
cJSON *json_scan_stream;
int isScanStream = 0;

void init(char *file_location)
{
  persistentFile = file_location;
  scan_persistent();
}

void cleanup()
{
  curl_exit_auth();
  curl_exit();
  if (isStream == 1)
  {
    free(json_stream);
  }
  if (isScanStream == 1)
  {
    cJSON_Delete(json_scan_stream);
  }
}

char *create_persistent_stream(char *username, char *audio_quality, char *video_quality)
{
  char *string = NULL;
  cJSON *authorization_json = NULL;
  cJSON *user_json = NULL;
  cJSON *preferences_json = NULL;
  cJSON *refresh_token_json = NULL;
  cJSON *access_token_json = NULL;
  cJSON *expires_in_json = NULL;
  cJSON *id_json = NULL;
  cJSON *username_json = NULL;
  cJSON *country_code_json = NULL;
  cJSON *audio_quality_json = NULL;
  cJSON *video_quality_json = NULL;

  cJSON *output_json = cJSON_CreateObject();

  authorization_json = cJSON_CreateObject();
  cJSON_AddItemToObject(output_json, "authorization", authorization_json);
  user_json = cJSON_CreateObject();
  cJSON_AddItemToObject(output_json, "user", user_json);
  preferences_json = cJSON_CreateObject();
  cJSON_AddItemToObject(output_json, "preferences", preferences_json);

  refresh_token_json = cJSON_CreateString(refresh_token);
  cJSON_AddItemToObject(authorization_json, "refresh_token", refresh_token_json);
  access_token_json = cJSON_CreateString(access_token);
  cJSON_AddItemToObject(authorization_json, "access_token", access_token_json);
  expires_in_json = cJSON_CreateNumber(expires_in);
  cJSON_AddItemToObject(authorization_json, "expires_in", expires_in_json);

  id_json = cJSON_CreateNumber(userId);
  cJSON_AddItemToObject(user_json, "id", id_json);
  username_json = cJSON_CreateString(username);
  cJSON_AddItemToObject(user_json, "username", username_json);
  country_code_json = cJSON_CreateString(countryCode);
  cJSON_AddItemToObject(user_json, "country_code", country_code_json);

  audio_quality_json = cJSON_CreateString(audio_quality);
  cJSON_AddItemToObject(preferences_json, "audio_quality", audio_quality_json);
  video_quality_json = cJSON_CreateString(video_quality);
  cJSON_AddItemToObject(preferences_json, "video_quality", video_quality_json);

  string = cJSON_Print(output_json); /* Allocate Memory (needs to be deallocated)  */
  json_stream = string;
  isStream = 1;
  cJSON_Delete(output_json);
  return string;
}

void read_persistent_stream(cJSON *input_json)
{
  cJSON *authorization_json = cJSON_GetObjectItem(input_json, "authorization");
  cJSON *user_json = cJSON_GetObjectItem(input_json, "user");
  cJSON *id_json = cJSON_GetObjectItem(user_json, "id");
  cJSON *refresh_token_json = cJSON_GetObjectItemCaseSensitive(authorization_json, "refresh_token");
  cJSON *access_token_json = cJSON_GetObjectItemCaseSensitive(authorization_json, "access_token");
  cJSON *expires_in_json = cJSON_GetObjectItem(authorization_json, "expires_in");
  cJSON *country_code_json = cJSON_GetObjectItemCaseSensitive(user_json, "country_code");
  cJSON *preferences_json = cJSON_GetObjectItem(input_json, "preferences");
  cJSON *audio_quality_json = cJSON_GetObjectItemCaseSensitive(preferences_json, "audio_quality");
  cJSON *video_quality_json = cJSON_GetObjectItemCaseSensitive(preferences_json, "video_quality");

  refresh_token = refresh_token_json->valuestring;
  access_token = access_token_json->valuestring;
  expires_in = expires_in_json->valueint;
  userId = id_json->valueint;
  countryCode = country_code_json->valuestring;
  audioQuality = audio_quality_json->valuestring;
  videoQuality = video_quality_json->valuestring;
}

void scan_persistent()
{
  FILE *persistentJSON;
  long streamSize;
  char *stream;
  int error = 0;

  /* open persistentFile  */
  persistentJSON = fopen(persistentFile, "rb");
  if (!persistentJSON)
  {
    fprintf(stderr, "[OAuth] File not found. Authenticate!\n");
    error = 1;
    goto end;
  }

  fseek(persistentJSON, 0L, SEEK_END);
  streamSize = ftell(persistentJSON);
  rewind(persistentJSON);

  /* allocate memory for entire content */
  stream = calloc( 1, streamSize+1 );
  if( !stream )
  {
    fclose(persistentJSON);
    fprintf(stderr, "memory alloc fails");
    error = 1;
    goto end;
  }

  /* copy the file into the buffer */
  if( 1!=fread( stream , streamSize, 1 , persistentJSON) )
  {
    fclose(persistentJSON);
    free(stream);
    fprintf(stderr, "entire read fails");
    error = 1;
    goto end;
  }
  fclose(persistentJSON);

  /* parse JSON stream  */
  cJSON *input_json = json_parse(stream);
  read_persistent_stream(input_json);
  isScanStream = 1;
  json_scan_stream = input_json;
  free(stream);
end:
  if (error == 1)
  {
    fprintf(stderr, "[OAuth] Scan persistentFile failed!\n");
  }
}

void create_persistent(char *username, char *audio_quality, char *video_quality)
{
  FILE *fp;
  fp = fopen(persistentFile, "w");
  if (fp != NULL)
  {
    char *json = create_persistent_stream(username, audio_quality, video_quality);
    fprintf(fp, "%s", json);
  }
  else
  {
    fprintf(stderr, "[OAuth] Failed to create persistentFile!\n");
  }
  fclose(fp);
}

void refresh_persistent()
{
  /* start OAuth refresh routine  */
  time_t currentTime = time(NULL);
  double diff_t;

  /* Check if ExpiryDate is in the future  */
  if (currentTime > expires_in)
  {
    diff_t = difftime(currentTime, expires_in);
  }
  else
  {
    diff_t = difftime(expires_in, currentTime);
  }
  //printf("Difference Size_t: %zu\n", (size_t) diff_t);

  /* If ExpiryDate is in the future with a difference of more than 5min  */
  if (currentTime < expires_in && (size_t) diff_t >= 300)
  {
    //printf("[OAuth] Renewal not necessary.\n");
  }
  /* Start renewal process  */
  else
  {
    login_token_model res = login_refresh_token(refresh_token);
    if (res.status == 1)
    {
      FILE *fp;
      access_token = res.access_token;
      userId = res.userId;
      expires_in = time(NULL) + 604800; /* Calculate new ExpiryDate */

      fp = fopen(persistentFile, "w");
      if (fp != NULL)
      {
        char *json = create_persistent_stream(res.username, audioQuality, videoQuality);
        fprintf(fp, "%s", json);
      }
      else
      {
        fprintf(stderr, "[OAuth] Failed to create persistentFile!\n");
      }
      fclose(fp);
    }
    else
    {
      fprintf(stderr, "[OAuth] Auto Refresh failed.\n");
      sleep(30);
    }
  }
}
