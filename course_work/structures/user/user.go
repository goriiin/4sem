package user

import (
	"github.com/goriiin/cw/structures/bank"
	"github.com/goriiin/cw/structures/transport"
	"time"
)

type RegistrationAddress struct {
	ID       int64  `db:"id"`
	City     string `db:"city"`
	Street   string `db:"street"`
	HouseNum string `db:"house_num"`
	Flat     int    `db:"flat"`
	Country  string `db:"country"`
}

type Human struct {
	ID             int64                `db:"id"`
	Surname        string               `db:"surname"`
	Name           string               `db:"name"`
	MidName        string               `db:"mid_name"`
	PassportSeries int                  `db:"passport_series"`
	PassportNum    int                  `db:"passport_num"`
	Birthday       time.Time            `db:"birthday"`
	RegAddress     *RegistrationAddress `db:"reg_address"`
}

type User struct {
	ID          int64      `db:"id"`
	Nick        string     `db:"nick"`
	BankData    *bank.Data `db:"bank_data"`
	Email       string     `db:"email"`
	PhoneNumber string     `db:"phone_number"`
	RegDate     time.Time  `db:"reg_date"`
	HumanID     int64      `db:"human_id"`
	Human       *Human     `db:"human"`
}

type DriverLicense struct {
	ID        int64     `db:"id"`
	Type      string    `db:"type"`
	BeginDate time.Time `db:"begin_date"`
	EndDate   time.Time `db:"end_date"`
	Num       string    `db:"num"`
}

type License struct {
	ID        int64          `db:"id"`
	UserID    int64          `db:"user_id"`
	LicenseID int64          `db:"licence_id"`
	User      *User          `db:"user"`
	License   *DriverLicense `db:"licence"`
}

type Rent struct {
	ID          int64                `db:"id"`
	TransportID int64                `db:"transport_id"`
	UserID      int64                `db:"user_id"`
	CostPerHour float64              `db:"cost_per_hour"`
	BeginDate   time.Time            `db:"begin_date"`
	EndDate     time.Time            `db:"end_date"`
	City        string               `db:"city"`
	Transport   *transport.Transport `db:"transport"`
	User        *User                `db:"user"`
}
