#include <stdlib.h>
#include <stdio.h>
#include "../include/openTIDAL.h"
#include <string.h>
#include <curl/curl.h>

#include <unistd.h>
#include "../include/base64.h"

char *client_id = "8SEZWa4J1NVC5U5Y";
char *client_secret = "owUYDkxddz+9FpvGX24DlxECNtFEMBxipU0lBfrbq60=";
char *audioQuality = "LOSSLESS";
char *videoQuality = "HIGH";
char *countryCode = "DE";
char *access_token;

int main(void)
{
  size_t skipped;
  char input_token[1024];
  
  printf("Testing openTIDAL Playlist Endpoints...\n");
  printf("[CI] Enter your access_token: ");
  scanf("%s", input_token); /* Pls no BufferOverflow :( */
  access_token = input_token;

  /* get_playlist  */
  skipped = 1;
  printf("[CI] Testing get_playlist (0 to skip)...: ");
  scanf("%zu", &skipped);
  if (skipped != 0)
  {
    playlist_model res = get_playlist("854e65fb-857a-4db3-9108-4be406e8ea3d");
    if (res.status == 1)
    {
      printf("NumberOfTracks: %zu\n", res.numberOfTracks[0]);
      printf("NumberOfVideos: %zu\n", res.numberOfVideos[0]);
      printf("Uuid: %s\n", res.uuid[0]);
      printf("Title: %s\n", res.title[0]);
      if (res.hasDescription[0] != 0)
      {
        printf("Description: %s\n", res.description[0]);
      }
      printf("Duration: %zu\n", res.duration[0]);
      printf("Last Updated: %s\n", res.lastUpdated[0]);
      printf("Created: %s\n", res.created[0]);
      printf("Image: %s\n", res.image[0]);
      printf("Square Image: %s\n", res.squareImage[0]);
      printf("Popularity: %zu\n", res.popularity[0]);
    }
  }
  else
  {
    printf("[CI] Skipping...\n");
  }

  /* get_playlist_items */
  skipped = 1;
  printf("[CI] Testing get_playlist_items (0 to skip)...: ");
  scanf("%zu", &skipped);
  if (skipped != 0)
  {
    size_t limit;
    size_t offset;

    printf("[CI] Limit: ");
    scanf("%zu", &limit);
    printf("[CI] Offset: ");
    scanf("%zu", &offset);

    items_model res = get_playlist_items("854e65fb-857a-4db3-9108-4be406e8ea3d", limit, offset);
    if (res.status == 1)
    {
      int i;
      for (i = 0; i < res.arraySize; ++i)
      {
        printf("Id: %zu\n", res.id[i]);
        printf("Title: %s\n", res.title[i]);
        printf("Duration: %zu\n", res.duration[i]);
        printf("Popularity: %zu\n", res.popularity[i]);
        printf("TrackNumber: %zu\n", res.trackNumber[i]);
        printf("VolumeNumber: %zu\n", res.volumeNumber[i]);
        printf("AlbumId: %zu\n", res.albumId[i]);
        printf("AlbumTitle: %s\n", res.albumTitle[i]);
        printf("Cover: %s\n", res.cover[i]);
        printf("Quality: %s\n", res.quality[i]);
        if (res.hasVersion[i])
        {
          printf("Version: %s\n", res.version[i]);
        }
        size_t a;
        for (a = 0; a < res.subArraySize[i]; ++a)
        {
          printf("ArtistName #%zu: %s\n", a, res.artistName[i][a]);
          printf("ArtistId #%zu: %zu\n", a, res.artistId[i][a]);
        }
      }
    }
  }
  else
  {
    printf("[CI] Skipping...\n");
  }

  /* delete_playlist */
  skipped = 1;
  printf("[CI] Testing delete_playlist (0 to skip)...: ");
  scanf("%zu", &skipped);
  if (skipped != 0)
  {
    char playlist[40];
    printf("[CI] Playlist: ");
    scanf("%s", playlist);

    int res = delete_playlist(playlist);
    if (res == 1)
    {
      printf("[CI] Success!\n");
    }
  }
  else
  {
    printf("[CI] Skipping...\n");
  }
  
  /* delete_playlist_item */
  skipped = 1;
  printf("[CI] Testing delete_playlist_item (0 to skip)...: ");
  scanf("%zu", &skipped);
  if (skipped != 0)
  {
    char playlist[40];
    printf("[CI] Playlist: ");
    scanf("%s", playlist);
    
    char *eTag = get_playlist_etag(playlist);
    if (eTag != 0)
    {
      int res = delete_playlist_item(playlist, 0, eTag);
      free(eTag);
      if (res == 1)
      {
        printf("[CI] Success!\n");
      }
    }
  }
  else
  {
    printf("[CI] Skipping...\n");
  }

  /* move_playlist_item */
  printf("[CI] Skipping move_playlist_item (Broken)...\n");

  /* add_playlist_item */
  printf("[CI] Skipping add_playlist_item (Broken)...\n");
  printf("[CI] Skipping add_playlist_items (Broken)...\n");
}
