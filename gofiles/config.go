package main

import "C"
import (
	"log"

	"os/user"
	"os"

	"regexp"

	"io/ioutil"
)

var confBytes []byte;

func conf(){
	log.Println("Trying to retrieve key from config file")
	if confFile == "" {
		usr, err := user.Current()
		if err != nil { return; }
		confFile = usr.HomeDir + "/.config/yttui/config"
	}

	conf , err := os.Open(confFile)
	defer conf.Close()
	if err != nil { return; }
	confB, err := ioutil.ReadAll(conf)
	if err != nil { return; }
	confBytes = confB

	re := regexp.MustCompile("key:\t.+")
	keyLine := re.Find(confBytes)
	re = regexp.MustCompile("\t.+")
	key := string(re.Find(keyLine))
	if len(key) < 40 {
		log.Println("Error: Invalid API key.")
	}
	developerKey =  key[1:40]
	log.Println("found" + findOpt("pady"));
}

func findOpt(opt string) (string) {
	re := regexp.MustCompile(opt + ":\t.+")
	keyLine := re.Find(confBytes)
	re = regexp.MustCompile("\t.+")
	str := string(re.Find(keyLine))
	return string(str)
}
