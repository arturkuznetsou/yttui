package main
import "C"

import (
	"log"
        "google.golang.org/api/youtube/v3"
)

const developerKey = "<++>"
const videoPerRetrieval = 50

// allowed strings: moderate, none, strict
var safeSearchVar = "none"
// allowed strings: moderate, none, strict

// ISO 639-1 codes http://www.loc.gov/standards/iso639-2/php/code_list.php
var relevanceLanguageVar = "en"

var videoBuffer []video

var service *youtube.Service
var err error



func main() {}


//export getTitleC
func getTitleC (index C.int) *C.char {
		return C.CString(videoBuffer[index].response.Snippet.Title)
}


//export getLikesC
func getLikesC (index C.int) uint64 {
		return videoBuffer[index].response.Statistics.LikeCount
}



//export getDislikesC
func getDislikesC (index C.int) uint64 {
		return videoBuffer[index].response.Statistics.DislikeCount
}




//export getViewsC
func getViewsC (index C.int) uint64 {
		return videoBuffer[index].response.Statistics.ViewCount
}



//export getChannelNameC
func getChannelNameC (index C.int) *C.char {
		return C.CString(videoBuffer[index].response.Snippet.ChannelTitle)
}



//export getChannelIdC
func getChannelIdC (index C.int) *C.char {
		return C.CString(videoBuffer[index].response.Snippet.ChannelId)
}




//export getDateC
func getDateC (index C.int) *C.char {
		return C.CString(videoBuffer[index].response.Snippet.PublishedAt)
}



//export getIdC
func getIdC (index C.int) *C.char {
	return C.CString(videoBuffer[index].response.Id)
}

//export getDescriptionC
func getDescriptionC (index C.int) *C.char {
	return C.CString (videoBuffer[index].response.Snippet.Description)}

//export getBufferLen
func getBufferLen() int {
	return len(videoBuffer)
}

//export videoPageIdC
func videoPageIdC (pageId *C.char) *C.char {
	id := C.GoString(pageId)
	err, nextPage := videoPageId (service, id, videoPerRetrieval, &videoBuffer)

	if err != nil { return C.CString ("#ERROR#" + err.Error()) }
	return C.CString (nextPage)
}

//export videoSearchC
func videoSearchC (search *C.char) *C.char {
	searchterm := C.GoString (search)
	err, nextPage := videoSearch (service, searchterm, videoPerRetrieval, &videoBuffer)

	if err != nil {
		//The string length of 6 is reserved to non-error returns. (Janky solution, I know)
		if len(err.Error()) == 6 {
			return C.CString (" " + err.Error())
		}
		return C.CString (err.Error())
	}

	return C.CString(nextPage)
}

//export videoMostPopularC
func videoMostPopularC () *C.char {

	err, nextPage := videoMostPopular (service, videoPerRetrieval, &videoBuffer)

	if err != nil {
		//The string length of 6 is reserved to non-error returns. (Janky solution, I know)
		if len(err.Error()) == 6 {
			return C.CString (" " + err.Error())
		}
		return C.CString (err.Error())
	}
	return C.CString(nextPage)
}




//export clearBuffGo
func clearBuffGo () {
	log.Printf("Clearing buffer\n")
	videoBuffer = nil
}
//export printBuffer
func printBuffer() {
	for index, item  := range videoBuffer {
		log.Printf("\n%d Recieved Title: %s (Views: %d)", index, item.response.Snippet.ChannelTitle, item.response.Statistics.ViewCount)
	}
}
//export logPrintln
func logPrintln (logMessage *C.char) {
	log.Println(C.GoString (logMessage));
}
//export __init__
func __init__() {

	setLogToFile()


	service, err = getServiceWithoutLogin()

	handleError(err, "")
}




//export setSafeSearchC
func setSafeSearchC (str *C.char) {
	relevanceLanguageVar = C.GoString(str)
}

//export setLangC
func setLangC (str *C.char) {
	relevanceLanguageVar = C.GoString(str)
}

