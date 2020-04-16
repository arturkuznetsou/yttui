package main

import "C"
import (
	"log"

	"net/http"

	"google.golang.org/api/googleapi/transport"
	"google.golang.org/api/youtube/v3"
)



func getServiceWithoutLogin() (*youtube.Service, error) {
	log.Println("Getting service without login")
	client := &http.Client{
		Transport: &transport.APIKey{Key: developerKey},
	}
	defer log.Println("Done")
	return youtube.New(client)
}
