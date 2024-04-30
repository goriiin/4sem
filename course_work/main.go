package main

import (
	"github.com/goriiin/cw/config"
	"github.com/goriiin/cw/pages"
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

	t, err := template.New("base").ParseFiles("./templates/index.gohtml", "./templates/my_Content.gohtml")
	if err != nil {
		log.Fatal(err)
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		page := pages.BasePage{Content: "КУРСОВАЯ ПО БД"}
		err := t.ExecuteTemplate(w, "index.gohtml", page)
		if err != nil {
			log.Fatalf("template error : %s", err)
		}
	})

	http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("./static"))))

	_ = http.ListenAndServe(":8080", nil)
}
