package main

import "C"
import (
	"log"

	"net/http"

	"google.golang.org/api/googleapi/transport"
	"google.golang.org/api/youtube/v3"

	"os/user"
	"os"

	"regexp"

	"io/ioutil"
)



func getServiceWithoutLogin() (*youtube.Service, error) {
	log.Println("Getting service without login")
	client := &http.Client{
		Transport: &transport.APIKey{Key: developerKey},
	}
	defer log.Println("Done")
	return youtube.New(client)
}

func getKeyFromFile() (string, error) {
	log.Println("Trying to retrieve key from config file")
	if confFile == "" {
		usr, err := user.Current()
		if err != nil { return "", err }
		confFile = usr.HomeDir + "/.config/yttui/config"
	}

	conf , err := os.Open(confFile)
	defer conf.Close()
	if err != nil { return "", err }
	confBytes, err := ioutil.ReadAll(conf)
	if err != nil { return "", err }

	re := regexp.MustCompile("key:\t.+")
	keyLine := re.Find(confBytes)
	re = regexp.MustCompile("\t.+")
	key := string(re.Find(keyLine))
	if len(key) < 40 {
		log.Println("Error: Invalid API key.")
		return "", err
	}
	log.Println("key: " + key[1:40])
	return key[1:40], err
}
