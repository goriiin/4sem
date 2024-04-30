package structures

type BankData struct {
	ID   int64  `db:"id"`
	Num  string `db:"num"`
	Date string `db:"date"`
	CVC  int    `db:"cvc"`
}

type Cheque struct {
	ID            int64   `db:"id"`
	RentID        int64   `db:"rent_id"`
	UserID        int64   `db:"user_id"`
	TotalCost     float64 `db:"total_cost"`
	PaymentStatus bool    `db:"payment_status"`
	Rent          *Rent   `db:"rent"`
	User          *User   `db:"user"`
}
