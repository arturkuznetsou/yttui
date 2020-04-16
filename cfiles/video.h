#ifndef YT_VIDEO_H
#define YT_VIDEO_H

#include "../gotoc.h"
#include <stdint.h>



struct vidBuf{
	char** title;
	char** id;

	char** channelName;
	char** channelId;

	char** date;

	uint64_t* views;
	uint64_t* likes;
	uint64_t* dislikes;

	int size;
};
void fillInfo (struct vidBuf* vid);
void clearBuffer (struct vidBuf* vid);


#endif
