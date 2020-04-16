package main
import "C"
import (
	"google.golang.org/api/youtube/v3"
)
func constructIdListVid (itemList []*youtube.Video) string {

	var idList string
	for index, item := range itemList {
		if index > 1 && item.Id != "" {
			idList += ","
			idList += item.Id
		}else{
			idList += item.Id
		}
	}
	return idList
}
func constructIdListSrc (itemList []*youtube.SearchResult) string {

	var idList string
	for index, item := range itemList {
		if index > 1 && item.Id.VideoId != "" {
			idList += ","
			idList += item.Id.VideoId
		}else{
			idList += item.Id.VideoId
		}
	}
	return idList
}
