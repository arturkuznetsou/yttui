#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "video.h"
#include "../gotoc.h"


void fillInfo (struct vidBuf* vid) {
	logPrintln ("Constructing C buffer");
	logPrintln ("Allocating memory");

	size_t size = getBufferLen();



	vid->size = size;

	vid->title = malloc ( sizeof(char*) * size);
	vid->id = malloc ( sizeof(char*) * size);

	vid->channelName = malloc ( sizeof(char*) * size);
	vid->channelId = malloc ( sizeof(char*) * size);

	vid->date = malloc ( sizeof(char*) * size);

	vid->likes = malloc ( sizeof(uint64_t) * size);
	vid->dislikes = malloc ( sizeof(uint64_t) * size);
	vid->views = malloc ( sizeof(uint64_t) * size);

	logPrintln ("Done allocating");



	logPrintln ("Setting values");
	for ( int n = 0; n < size; n++) {

		vid->title[n] = getTitleC (n);
		vid->id[n] = getIdC (n);

		vid->channelName[n] = getChannelNameC (n);
		vid->channelId[n] = getChannelIdC (n);

		vid->date[n] = getDateC (n);

		vid->likes[n] = getLikesC (n);
		vid->dislikes[n] = getDislikesC (n);
		vid->views[n] = getViewsC (n);
	}

	logPrintln ("Done");
}

void clearBuffer (struct vidBuf* vid) {
	free (vid->title);
	free (vid->id);

	free (vid->channelName);
	free (vid->channelId);

	free (vid->date);

	free (vid->likes);
	free (vid->dislikes);
	free (vid->views);

	vid->size = 0;
}
