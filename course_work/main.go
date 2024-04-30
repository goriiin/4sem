package main

import (
	"github.com/goriiin/cw/config"
	"github.com/goriiin/cw/storage"
	"html/template"
	"log"
	"net/http"
	"os"
)

func main() {
	cfg := config.MustLoad()
	s, err := storage.New(cfg.DbConfigPath)

	if err != nil {
		log.Fatalf("db error : %s", err)
		os.Exit(1)
	}
	err = s.TestSelect()
	if err != nil {
		log.Fatalf("db error : %s", err)
		os.Exit(1)
	}

	t, err := template.New("base").ParseFiles("base.gohtml", "user.gohtml")
	if err != nil {
		log.Fatal(err)
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		users := []UserData{
			{Name: "John Doe", Email: "johndoe@example.com", Address: "123 Main St, Anytown, USA"},
			{Name: "Jane Doe", Email: "janedoe@example.com", Address: "456 Elm St, Othertown, USA"},
			{Name: "Bob Smith", Email: "bobsmith@example.com", Address: "789 Oak St, Thistown, USA"},
			// ... add more user records here ...
		}

		data := struct {
			Title string
			Users []UserData
		}{
			Title: "User Profiles",
			Users: users,
		}
		_ = t.Execute(w, data)
	})

	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("./static"))))

	_ = http.ListenAndServe(":8080", nil)
}

type UserData struct {
	Name    string
	Email   string
	Address string
}
