package structures

import "time"

type TransportInfo struct {
	ID          int64  `db:"id"`
	Brand       string `db:"brand"`
	ReleaseYear int    `db:"release_year"`
	Model       string `db:"model"`
}

type Damage struct {
	ID          int64  `db:"id"`
	MachinePart string `db:"machine_part"`
	Description string `db:"description"`
	Severity    int    `db:"severity"`
}

type GeneralInfo struct {
	ID          int64  `db:"id"`
	CheckupDate int    `db:"checkup_date"`
	EngineType  string `db:"engine_type"`
	Color       string `db:"color"`
	Description string `db:"description"`
}

type Transport struct {
	ID              int64          `db:"id"`
	GeneralInfoID   int64          `db:"general_info_id"`
	TransportInfoID int64          `db:"transport_info_id"`
	Free            bool           `db:"free"`
	StateNumber     string         `db:"state_number"`
	DateAdd         time.Time      `db:"date_add"`
	GeneralInfo     *GeneralInfo   `db:"general_info"`
	TransportInfo   *TransportInfo `db:"transport_info"`
}

type TransportDamages struct {
	ID          int64      `db:"id"`
	TransportID int64      `db:"transport_id"`
	DamageID    int64      `db:"damage_id"`
	Transport   *Transport `db:"transport"`
	Damage      *Damage    `db:"damage"`
}
