package main
import "C"
import (
	"google.golang.org/api/youtube/v3"
	"log"
)

func applySearchSettings(service *youtube.SearchListCall) *youtube.SearchListCall {
	if safeSearchVar == "moderate" || safeSearchVar == "none" || safeSearchVar == "strict" {
		service = service.SafeSearch(safeSearchVar)
	} else{
		log.Printf("\nError. SafeSearchVar improperly defined; '%s', instead of 'none', 'moderate' or 'strict'", safeSearchVar)
	}
	if relevanceLanguageVar != "" {
		log.Println("Setting relevance language," + relevanceLanguageVar)
		service = service.RelevanceLanguage(relevanceLanguageVar)
	}




	return service
}
