package main
import "C"
import (
	"log"
	"os/user"
	"os"

	"fmt"
)

func setLogToFile() {
	usr, err := user.Current()
	handleError (err, "Could not retrieve current user.")

	logDest := usr.HomeDir + "/.config/yttui/log"
	file, err := os.OpenFile (logDest, os.O_CREATE | os.O_WRONLY | os.O_APPEND, 0666)

	handleError (err, "Error opening log file.")
	log.SetOutput(file)
}
func handleError(err error, msg string) {
	if (err != nil) {
		log.Println(err.Error() + msg)
		fmt.Printf(err.Error() + msg)
	}
}

func handleFatalError(err error, msg string) {
	if err != nil {
		log.Fatalf("Fatal error.\n%v %v\n", msg, err.Error())
	}
}
