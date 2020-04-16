package main
import "C"
import (
	"time"
	"log"

	"google.golang.org/api/youtube/v3"
)





/* a structure to store all the necessary data of a video */
/* a structure to store all the necessary data of a video */
/* a structure to store all the necessary data of a video */
type video struct {
	date string
	channel string
	title string
	id string

	views uint64
	response *youtube.Video
}

/* Function that saves generated metadata in a buffer (buffer variable) */
/* Function that saves generated metadata in a buffer (buffer variable) */
/* Function that saves generated metadata in a buffer (buffer variable) */
func saveVideoStatistics (service *youtube.Service, videoId string, buffer *[]video)  error {
	call := service.Videos.List("id,snippet,statistics").Id(videoId)
	resp, err := call.Do()
	handleError(err, "\nAPI call error. Exiting.")
	if (err != nil) { return err}


	for _, item := range resp.Items {
		var newVid video
		newVid.response = item
		*buffer = append(*buffer, newVid)
	}

	return err
}
/* Function that saves generated metadata in a buffer (buffer variable) */
/* Function that saves generated metadata in a buffer (buffer variable) */
/* Function that saves generated metadata in a buffer (buffer variable) */


func videoMostPopular (service *youtube.Service, max int64, buffer *[]video) (error, string) {
	call := service.Videos.List("snippet").Chart("mostPopular").MaxResults(max)
	response, err := call.Do()
	handleError(err, "\nAPI call error. Exiting.")
	if (err != nil) { return err, "" }

	idList := constructIdListVid (response.Items)
	err = saveVideoStatistics (service, idList, buffer)

	log.Printf("\n\n results: %v \n\n", response)

	return err, response.NextPageToken
}
/* search results */
/* search results */
/* search results */
func videoPageId(service *youtube.Service, id string, max int64, buffer *[]video) (error, string) {

	begin := time.Now()
	call := applySearchSettings(service.Search.List("id,snippet").PageToken(id).MaxResults(max)).Type("video")
	response, err := call.Do()
	handleError(err, "\nAPI call error. Exiting.")
	if (err != nil) { return err, ""}


	end := time.Now()
	log.Printf("duration search: %v\n\n", end.Sub(begin))

	idList := constructIdListSrc (response.Items)


	err = saveVideoStatistics (service, idList, buffer)
	return err, response.NextPageToken
}


/* search results */
/* search results */
/* search results */
func videoSearch(service *youtube.Service, search string, max int64, buffer *[]video) (error, string) {

	log.Println("search: " + search)
	begin := time.Now()

	call := applySearchSettings(service.Search.List("id,snippet").Q(search).MaxResults(max)).Type("video")
	response, err := call.Do()

	handleError(err, "\nAPI call error. Exiting.")
	if (err != nil) { return err, ""}


	end := time.Now()
	log.Printf("duration search: %v\n\n", end.Sub(begin))

	idList := constructIdListSrc (response.Items)


	err = saveVideoStatistics (service, idList, buffer)
	return err, response.NextPageToken
}
/* most popular videos */
/* most popular videos */
/* most popular videos */

func getMostPopular(service *youtube.Service, max int64, buffer *[]video) error {


	call := service.Videos.List("id,snippet").Chart("mostPopular").MaxResults(50)
	response, err := call.Do()

	handleError(err, "\nAPI call error. Exiting.")
	if (err != nil) { return err}

	idList := constructIdListVid (response.Items)
	err = saveVideoStatistics (service, idList, buffer)

	return err
}


/* related videos */
/* related videos */
/* related videos */
func getRelatedTo (service *youtube.Service, videoId string, max int64, buffer *[]video) error {

	call := service.Search.List("id,snippet").RelatedToVideoId(videoId).MaxResults(max).Type("video")
	response, err := call.Do()
	handleError(err, "\nAPI call error. Exiting.")
	if err != nil { return err }

	idList := constructIdListSrc (response.Items)
	saveVideoStatistics (service, idList, buffer)

	return err
}

