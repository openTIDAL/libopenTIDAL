#include <stdio.h>
#include <stdlib.h>

#include "../src/include/openTIDAL.h"

int main()
{
  
  //openTIDAL_InitDemo();
  openTIDAL_Init("/Users/hugo/Documents/oT-config");
  openTIDAL resolve = openTIDAL_GetTrackStream(13479532);
  printf("%s\n", resolve.stream.url);

  openTIDAL_StructDelete(&resolve);
  openTIDAL_Cleanup();
  
  return 0;
}
