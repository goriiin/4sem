package structures

import "time"

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
	ID          int64     `db:"id"`
	Nick        string    `db:"nick"`
	BankData    *BankData `db:"bank_data"`
	Email       string    `db:"email"`
	PhoneNumber string    `db:"phone_number"`
	RegDate     time.Time `db:"reg_date"`
	HumanID     int64     `db:"human_id"`
	Human       *Human    `db:"human"`
}

type Fine struct {
	ID          int64   `db:"id"`
	Sum         float64 `db:"sum"`
	Description string  `db:"description"`
}

type UserFines struct {
	ID     int64     `db:"id"`
	UserID int64     `db:"user_id"`
	FineID int64     `db:"fine_id"`
	Date   time.Time `db:"date"`
	User   *User     `db:"user"`
	Fine   *Fine     `db:"fine"`
}

type DriverLicense struct {
	ID        int64     `db:"id"`
	Type      string    `db:"type"`
	BeginDate time.Time `db:"begin_date"`
	EndDate   time.Time `db:"end_date"`
	Num       string    `db:"num"`
}

type UserLicense struct {
	ID        int64          `db:"id"`
	UserID    int64          `db:"user_id"`
	LicenseID int64          `db:"licence_id"`
	User      *User          `db:"user"`
	License   *DriverLicense `db:"licence"`
}

type Rent struct {
	ID          int64      `db:"id"`
	TransportID int64      `db:"transport_id"`
	UserID      int64      `db:"user_id"`
	CostPerHour float64    `db:"cost_per_hour"`
	BeginDate   time.Time  `db:"begin_date"`
	EndDate     time.Time  `db:"end_date"`
	City        string     `db:"city"`
	Transport   *Transport `db:"transport"`
	User        *User      `db:"user"`
}
