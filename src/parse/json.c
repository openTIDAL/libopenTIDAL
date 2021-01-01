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

#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

json_login_code_model
json_parse_login_code (cJSON *directObject)
{
    json_login_code_model Value;

    Value.directObject = NULL;
    Value.deviceCode = NULL;
    Value.userCode = NULL;
    Value.verificationUri = NULL;
    Value.verificationUriComplete = NULL;
    Value.expiresIn = NULL;
    Value.interval = NULL;

    Value.directObject = directObject;
    Value.deviceCode = cJSON_GetObjectItemCaseSensitive (directObject, "deviceCode");
    Value.userCode = cJSON_GetObjectItemCaseSensitive (directObject, "userCode");
    Value.verificationUri = cJSON_GetObjectItemCaseSensitive (directObject, "verificationUri");
    Value.verificationUriComplete
        = cJSON_GetObjectItemCaseSensitive (directObject, "verificationUriComplete");
    Value.expiresIn = cJSON_GetObjectItem (directObject, "expiresIn");
    Value.interval = cJSON_GetObjectItem (directObject, "interval");

    return Value;
}

json_login_token_model
json_parse_login_token (cJSON *directObject)
{
    json_login_token_model Value;

    cJSON *user = NULL;
    Value.access_token = NULL;
    Value.refresh_token = NULL;
    Value.token_type = NULL;
    Value.expires_in = NULL;
    Value.userId = NULL;
    Value.email = NULL;
    Value.countryCode = NULL;
    Value.fullName = NULL;
    Value.firstName = NULL;
    Value.lastName = NULL;
    Value.nickname = NULL;
    Value.username = NULL;
    Value.imageId = NULL;
    Value.created = NULL;
    Value.updated = NULL;
    Value.facebookUid = NULL;
    Value.appleUid = NULL;

    user = cJSON_GetObjectItem (directObject, "user");
    Value.access_token = cJSON_GetObjectItemCaseSensitive (directObject, "access_token");
    Value.refresh_token = cJSON_GetObjectItemCaseSensitive (directObject, "refresh_token");
    Value.token_type = cJSON_GetObjectItemCaseSensitive (directObject, "token_type");
    Value.expires_in = cJSON_GetObjectItem (directObject, "expires_in");
    Value.userId = cJSON_GetObjectItemCaseSensitive (user, "userId");
    Value.email = cJSON_GetObjectItemCaseSensitive (user, "email");
    Value.countryCode = cJSON_GetObjectItemCaseSensitive (user, "countryCode");
    Value.fullName = cJSON_GetObjectItemCaseSensitive (user, "fullName");
    Value.firstName = cJSON_GetObjectItemCaseSensitive (user, "firstName");
    Value.lastName = cJSON_GetObjectItemCaseSensitive (user, "lastName");
    Value.nickname = cJSON_GetObjectItemCaseSensitive (user, "nickname");
    Value.username = cJSON_GetObjectItemCaseSensitive (user, "username");
    Value.imageId = cJSON_GetObjectItemCaseSensitive (user, "imageId");
    Value.created = cJSON_GetObjectItem (user, "created");
    Value.updated = cJSON_GetObjectItem (user, "updated");
    Value.facebookUid = cJSON_GetObjectItem (user, "facebookUid");
    Value.appleUid = cJSON_GetObjectItemCaseSensitive (user, "appleUid");

    return Value;
}

json_user_model
json_parse_user (cJSON *directObject)
{
    json_user_model Value;

    Value.directObject = NULL;
    Value.id = NULL;
    Value.username = NULL;
    Value.firstName = NULL;
    Value.lastName = NULL;
    Value.email = NULL;
    Value.countryCode = NULL;
    Value.created = NULL;
    Value.picture = NULL;
    Value.newsletter = NULL;
    Value.acceptedEULA = NULL;
    Value.gender = NULL;
    Value.dateOfBirth = NULL;
    Value.facebookUid = NULL;
    Value.appleUid = NULL;

    Value.directObject = directObject;
    Value.id = cJSON_GetObjectItem (directObject, "id");
    Value.username = cJSON_GetObjectItemCaseSensitive (directObject, "username");
    Value.firstName = cJSON_GetObjectItemCaseSensitive (directObject, "firstName");
    Value.lastName = cJSON_GetObjectItemCaseSensitive (directObject, "lastName");
    Value.email = cJSON_GetObjectItemCaseSensitive (directObject, "email");
    Value.countryCode = cJSON_GetObjectItemCaseSensitive (directObject, "countryCode");
    Value.created = cJSON_GetObjectItemCaseSensitive (directObject, "created");
    Value.picture = cJSON_GetObjectItemCaseSensitive (directObject, "picture");
    Value.newsletter = cJSON_GetObjectItem (directObject, "newsletter");
    Value.acceptedEULA = cJSON_GetObjectItem (directObject, "acceptedEULA");
    Value.gender = cJSON_GetObjectItemCaseSensitive (directObject, "gender");
    Value.dateOfBirth = cJSON_GetObjectItemCaseSensitive (directObject, "dateOfBirth");
    Value.facebookUid = cJSON_GetObjectItem (directObject, "facebookUid");
    Value.appleUid = cJSON_GetObjectItemCaseSensitive (directObject, "appleUid");

    return Value;
}

json_user_subscription_model
json_parse_user_subscription (cJSON *directObject)
{
    json_user_subscription_model Value;

    cJSON *subscription = NULL;
    Value.directObject = NULL;
    Value.validUntil = NULL;
    Value.status = NULL;
    Value.type = NULL;
    Value.offlineGracePeriod = NULL;
    Value.highestSoundQuality = NULL;
    Value.premiumAccess = NULL;
    Value.canGetTrial = NULL;
    Value.paymentType = NULL;

    subscription = cJSON_GetObjectItem (directObject, "subscription");
    Value.directObject = directObject;
    Value.validUntil = cJSON_GetObjectItemCaseSensitive (directObject, "validUntil");
    Value.status = cJSON_GetObjectItemCaseSensitive (directObject, "status");
    Value.type = cJSON_GetObjectItemCaseSensitive (subscription, "type");
    Value.offlineGracePeriod = cJSON_GetObjectItem (subscription, "offlineGracePeriod");
    Value.highestSoundQuality
        = cJSON_GetObjectItemCaseSensitive (directObject, "highestSoundQuality");
    Value.premiumAccess = cJSON_GetObjectItem (directObject, "premiumAccess");
    Value.canGetTrial = cJSON_GetObjectItem (directObject, "canGetTrial");
    Value.paymentType = cJSON_GetObjectItemCaseSensitive (directObject, "paymentType");

    return Value;
}

json_playlist_model
json_parse_playlist (cJSON *directObject)
{
    json_playlist_model Value;

    Value.directObject = NULL;
    Value.uuid = NULL;
    Value.title = NULL;
    Value.description = NULL;
    Value.popularity = NULL;
    Value.duration = NULL;
    Value.created = NULL;
    Value.lastUpdated = NULL;
    Value.numberOfTracks = NULL;
    Value.numberOfVideos = NULL;
    Value.publicPlaylist = NULL;
    Value.image = NULL;
    Value.squareImage = NULL;
    Value.type = NULL;

    Value.directObject = directObject;
    Value.uuid = cJSON_GetObjectItemCaseSensitive (directObject, "uuid");
    Value.title = cJSON_GetObjectItemCaseSensitive (directObject, "title");
    Value.description = cJSON_GetObjectItemCaseSensitive (directObject, "description");
    Value.popularity = cJSON_GetObjectItemCaseSensitive (directObject, "popularity");
    Value.duration = cJSON_GetObjectItemCaseSensitive (directObject, "duration");
    Value.created = cJSON_GetObjectItemCaseSensitive (directObject, "created");
    Value.lastUpdated = cJSON_GetObjectItemCaseSensitive (directObject, "lastUpdated");
    Value.numberOfTracks = cJSON_GetObjectItem (directObject, "numberOfTracks");
    Value.numberOfVideos = cJSON_GetObjectItem (directObject, "numberOfVideos");
    Value.publicPlaylist = cJSON_GetObjectItem (directObject, "publicPlaylist");
    Value.image = cJSON_GetObjectItemCaseSensitive (directObject, "image");
    Value.squareImage = cJSON_GetObjectItemCaseSensitive (directObject, "squareImage");
    Value.type = cJSON_GetObjectItemCaseSensitive (directObject, "type");

    return Value;
}

json_items_model
json_parse_items (cJSON *directObject)
{
    json_items_model Value;

    cJSON *artistsItem = NULL;
    Value.album = NULL;
    Value.directObject = NULL;
    Value.id = NULL;
    Value.title = NULL;
    Value.duration = NULL;
    Value.popularity = NULL;
    Value.trackNumber = NULL;
    Value.volumeNumber = NULL;
    Value.version = NULL;
    Value.cover = NULL;
    Value.videoCover = NULL;
    Value.imageId = NULL;
    Value.audioQuality = NULL;
    Value.quality = NULL;
    Value.explicitItem = NULL;
    Value.allowStreaming = NULL;
    Value.streamReady = NULL;
    Value.replayGain = NULL;
    Value.peak = NULL;
    Value.artists = NULL;
    Value.albumId = NULL;
    Value.albumTitle = NULL;
    Value.artistId = NULL;
    Value.artistName = NULL;

    Value.album = cJSON_GetObjectItem (directObject, "album");
    Value.directObject = directObject;
    Value.id = cJSON_GetObjectItem (directObject, "id");
    Value.title = cJSON_GetObjectItemCaseSensitive (directObject, "title");
    Value.duration = cJSON_GetObjectItem (directObject, "duration");
    Value.popularity = cJSON_GetObjectItem (directObject, "popularity");
    Value.trackNumber = cJSON_GetObjectItem (directObject, "trackNumber");
    Value.volumeNumber = cJSON_GetObjectItem (directObject, "volumeNumber");
    Value.version = cJSON_GetObjectItemCaseSensitive (directObject, "version");
    Value.cover = cJSON_GetObjectItemCaseSensitive (Value.album, "cover");
    Value.videoCover = cJSON_GetObjectItemCaseSensitive (Value.album, "videoCover");
    Value.imageId = cJSON_GetObjectItemCaseSensitive (directObject, "imageId");
    Value.audioQuality = cJSON_GetObjectItemCaseSensitive (directObject, "audioQuality");
    Value.quality = cJSON_GetObjectItemCaseSensitive (directObject, "quality");
    Value.explicitItem = cJSON_GetObjectItem (directObject, "explicit");
    Value.allowStreaming = cJSON_GetObjectItem (directObject, "allowStreaming");
    Value.streamReady = cJSON_GetObjectItem (directObject, "streamReady");
    Value.replayGain = cJSON_GetObjectItem (directObject, "replayGain");
    Value.peak = cJSON_GetObjectItem (directObject, "peak");
    Value.artists = cJSON_GetObjectItem (directObject, "artists");
    Value.albumId = cJSON_GetObjectItem (Value.album, "id");
    Value.albumTitle = cJSON_GetObjectItemCaseSensitive (Value.album, "title");

    if (cJSON_IsArray (Value.artists)) {
        int i = 0;
        Value.artistId = malloc (sizeof (cJSON *) * cJSON_GetArraySize (Value.artists));
        Value.artistName = malloc (sizeof (cJSON *) * cJSON_GetArraySize (Value.artists));
        cJSON_ArrayForEach (artistsItem, Value.artists)
        {
            Value.artistId[i] = cJSON_GetObjectItem (artistsItem, "id");
            Value.artistName[i] = cJSON_GetObjectItemCaseSensitive (artistsItem, "name");
            i += 1;
        }
    }

    return Value;
}

json_album_model
json_parse_album (cJSON *directObject)
{
    json_album_model Value;

    cJSON *artistsItem = NULL;
    Value.directObject = NULL;
    Value.id = NULL;
    Value.title = NULL;
    Value.duration = NULL;
    Value.popularity = NULL;
    Value.copyright = NULL;
    Value.quality = NULL;
    Value.cover = NULL;
    Value.videoCover = NULL;
    Value.releaseDate = NULL;
    Value.version = NULL;
    Value.explicitItem = NULL;
    Value.allowStreaming = NULL;
    Value.streamReady = NULL;
    Value.numberOfTracks = NULL;
    Value.numberOfVideos = NULL;
    Value.numberOfVolumes = NULL;
    Value.artists = NULL;
    Value.artistId = NULL;
    Value.artistName = NULL;

    Value.directObject = directObject;
    Value.id = cJSON_GetObjectItem (directObject, "id");
    Value.title = cJSON_GetObjectItemCaseSensitive (directObject, "title");
    Value.duration = cJSON_GetObjectItem (directObject, "duration");
    Value.popularity = cJSON_GetObjectItem (directObject, "popularity");
    Value.copyright = cJSON_GetObjectItemCaseSensitive (directObject, "copyright");
    Value.quality = cJSON_GetObjectItemCaseSensitive (directObject, "audioQuality");
    Value.cover = cJSON_GetObjectItemCaseSensitive (directObject, "cover");
    Value.videoCover = cJSON_GetObjectItemCaseSensitive (directObject, "videoCover");
    Value.releaseDate = cJSON_GetObjectItemCaseSensitive (directObject, "releaseDate");
    Value.version = cJSON_GetObjectItemCaseSensitive (directObject, "version");
    Value.explicitItem = cJSON_GetObjectItem (directObject, "explicit");
    Value.allowStreaming = cJSON_GetObjectItem (directObject, "allowStreaming");
    Value.streamReady = cJSON_GetObjectItem (directObject, "streamReady");
    Value.numberOfTracks = cJSON_GetObjectItem (directObject, "numberOfTracks");
    Value.numberOfVideos = cJSON_GetObjectItem (directObject, "numberOfVideos");
    Value.numberOfVolumes = cJSON_GetObjectItem (directObject, "numberOfVolumes");
    Value.artists = cJSON_GetObjectItem (directObject, "artists");

    if (cJSON_IsArray (Value.artists)) {
        int i = 0;
        Value.artistId = malloc (sizeof (cJSON *) * cJSON_GetArraySize (Value.artists));
        Value.artistName = malloc (sizeof (cJSON *) * cJSON_GetArraySize (Value.artists));
        cJSON_ArrayForEach (artistsItem, Value.artists)
        {
            Value.artistId[i] = cJSON_GetObjectItem (artistsItem, "id");
            Value.artistName[i] = cJSON_GetObjectItemCaseSensitive (artistsItem, "name");
            i += 1;
        }
    }

    return Value;
}

json_artist_model
json_parse_artist (cJSON *directObject)
{
    json_artist_model Value;

    Value.directObject = NULL;
    Value.id = NULL;
    Value.name = NULL;
    Value.picture = NULL;
    Value.popularity = NULL;

    Value.directObject = directObject;
    Value.id = cJSON_GetObjectItem (directObject, "id");
    Value.name = cJSON_GetObjectItemCaseSensitive (directObject, "name");
    Value.picture = cJSON_GetObjectItemCaseSensitive (directObject, "picture");
    Value.popularity = cJSON_GetObjectItem (directObject, "popularity");

    return Value;
}

json_links_model
json_parse_links (cJSON *directObject)
{
    json_links_model Value;

    Value.directObject = NULL;
    Value.url = NULL;
    Value.siteName = NULL;

    Value.directObject = directObject;
    Value.url = cJSON_GetObjectItemCaseSensitive (directObject, "url");
    Value.siteName = cJSON_GetObjectItemCaseSensitive (directObject, "siteName");

    return Value;
}

json_credit_model
json_parse_credits (cJSON *directObject)
{
    json_credit_model Value;

    Value.directObject = NULL;
    Value.type = NULL;
    Value.name = NULL;
    Value.id = NULL;

    Value.directObject = directObject;
    Value.type = cJSON_GetObjectItemCaseSensitive (directObject, "type");
    Value.name = cJSON_GetObjectItemCaseSensitive (directObject, "name");
    Value.id = cJSON_GetObjectItemCaseSensitive (directObject, "id");

    return Value;
}

json_contributor_model
json_parse_contributors (cJSON *directObject)
{
    json_contributor_model Value;

    Value.directObject = NULL;
    Value.name = NULL;
    Value.role = NULL;

    Value.directObject = directObject;
    Value.name = cJSON_GetObjectItemCaseSensitive (directObject, "name");
    Value.role = cJSON_GetObjectItemCaseSensitive (directObject, "role");

    return Value;
}

json_mix_model
json_parse_mix (cJSON *directObject)
{
    json_mix_model Value;

    cJSON *images = NULL;
    cJSON *SMALL = NULL;
    cJSON *MEDIUM = NULL;
    cJSON *LARGE = NULL;

    Value.directObject = NULL;
    Value.id = NULL;
    Value.title = NULL;
    Value.subTitle = NULL;
    Value.smallImageWidth = NULL;
    Value.smallImageHeight = NULL;
    Value.smallImageUrl = NULL;
    Value.mediumImageWidth = NULL;
    Value.mediumImageHeight = NULL;
    Value.mediumImageUrl = NULL;
    Value.largeImageWidth = NULL;
    Value.largeImageHeight = NULL;
    Value.largeImageUrl = NULL;
    Value.mixType = NULL;

    images = cJSON_GetObjectItem (directObject, "images");
    SMALL = cJSON_GetObjectItem (images, "SMALL");
    MEDIUM = cJSON_GetObjectItem (images, "MEDIUM");
    LARGE = cJSON_GetObjectItem (images, "LARGE");

    Value.directObject = directObject;
    Value.id = cJSON_GetObjectItemCaseSensitive (directObject, "id");
    Value.title = cJSON_GetObjectItemCaseSensitive (directObject, "title");
    Value.subTitle = cJSON_GetObjectItemCaseSensitive (directObject, "subTitle");
    Value.smallImageWidth = cJSON_GetObjectItem (SMALL, "width");
    Value.smallImageHeight = cJSON_GetObjectItem (SMALL, "height");
    Value.smallImageUrl = cJSON_GetObjectItemCaseSensitive (SMALL, "url");
    Value.mediumImageWidth = cJSON_GetObjectItem (MEDIUM, "width");
    Value.mediumImageHeight = cJSON_GetObjectItem (MEDIUM, "height");
    Value.mediumImageUrl = cJSON_GetObjectItemCaseSensitive (MEDIUM, "url");
    Value.largeImageWidth = cJSON_GetObjectItem (LARGE, "width");
    Value.largeImageHeight = cJSON_GetObjectItem (LARGE, "height");
    Value.largeImageUrl = cJSON_GetObjectItemCaseSensitive (LARGE, "url");
    Value.mixType = cJSON_GetObjectItemCaseSensitive (directObject, "mixType");

    return Value;
}

json_stream_model
json_parse_stream (cJSON *directObject)
{
    json_stream_model Value;

    Value.directObject = NULL;
    Value.trackId = NULL;
    Value.videoId = NULL;
    Value.assetPresentation = NULL;
    Value.audioQuality = NULL;
    Value.audioMode = NULL;
    Value.videoQuality = NULL;
    Value.manifestMimeType = NULL;
    Value.manifest = NULL;

    Value.directObject = directObject;
    Value.trackId = cJSON_GetObjectItem (directObject, "trackId");
    Value.videoId = cJSON_GetObjectItem (directObject, "videoId");
    Value.assetPresentation = cJSON_GetObjectItemCaseSensitive (directObject, "assetPresentation");
    Value.audioQuality = cJSON_GetObjectItemCaseSensitive (directObject, "audioQuality");
    Value.audioMode = cJSON_GetObjectItemCaseSensitive (directObject, "audioMode");
    Value.videoQuality = cJSON_GetObjectItemCaseSensitive (directObject, "videoQuality");
    Value.manifestMimeType = cJSON_GetObjectItemCaseSensitive (directObject, "manifestMimeType");
    Value.manifest = cJSON_GetObjectItemCaseSensitive (directObject, "manifest");

    return Value;
}

json_manifest_model
json_parse_manifest (cJSON *directObject)
{
    json_manifest_model Value;

    Value.directObject = NULL;
    Value.mimeType = NULL;
    Value.codec = NULL;
    Value.encryptionType = NULL;
    Value.urls = NULL;
    Value.url = NULL;

    Value.directObject = directObject;
    Value.mimeType = cJSON_GetObjectItemCaseSensitive (directObject, "mimeType");
    Value.codec = cJSON_GetObjectItemCaseSensitive (directObject, "codecs");
    Value.encryptionType = cJSON_GetObjectItemCaseSensitive (directObject, "encryptionType");
    Value.urls = cJSON_GetObjectItemCaseSensitive (directObject, "urls");

    if (cJSON_IsArray (Value.urls)) {
        Value.url = cJSON_GetArrayItem (Value.urls, 0);
    }

    return Value;
}
