/*
    Copyright (c) 2020-2021 Hugo Melder and openTIDAL contributors

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

/* OTService get tests
 */

#include "../../Source/openTIDAL.h"
#include <stdio.h>

int
main (int argc, char *argv[])
{
    struct OTSessionContainer *session = NULL;
    struct OTContentContainer *content = NULL;
    enum OTTypes type = CONTENT_CONTAINER;
    enum OTStatus statusPlaylist;
    session = OTSessionInit ();
    if (!session) return -1;

    if (!(OTSessionClientPair (session, "OmDtrzFgyVVL6uW56OnFA2COiabqm",
                               "zxen1r3pO0hgtOC7j6twMo9UAqngGrmRiWpV7QC1zJ8=")
          == 0))
        return -1;

    int status = OTSessionLogin (session, "/home/hugo/.config/openTIDAL/authrc");
    if (status != 0) goto end;

    session->verboseMode = 1;

    printf ("Proceed...\n");

    content = OTServiceCreatePlaylist (session, "Testing from openTIDAL",
                                       "This is a native TIDAL API client", NULL);
    OTDeallocContainer (content, type);

    statusPlaylist = OTServiceAddPlaylistItem (session, "9a1d6a6b-3405-4090-89f3-a04218a07764",
                                               "62929297", "SKIP", "SKIP", NULL);
end:
    OTSessionCleanup (session);
    return 0;
}
