package main

import "C"
import (
	"log"

	"os/user"
	"os"

	"regexp"

	"io/ioutil"

	"strconv"
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

	developerKey = findOpt("key")
	opt := findOpt("pady")
	if(opt != ""){ pady, err = strconv.Atoi(opt); }
	opt = findOpt("padx")
	if(opt != ""){ padx, err = strconv.Atoi(opt); }
}

func findOpt(opt string) (string) {
	re := regexp.MustCompile(opt + ":\t.+")
	keyLine := re.Find(confBytes)
	re = regexp.MustCompile("\t.+")
	str := string(re.Find(keyLine))
	if(str != ""){
		return string(str)[1:]
	}
	return ""
}
