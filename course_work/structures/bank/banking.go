package bank

import (
	"github.com/goriiin/cw/structures/user"
	"time"
)

type Cheque struct {
	ID            int64      `db:"id"`
	RentID        int64      `db:"rent_id"`
	UserID        int64      `db:"user_id"`
	TotalCost     float64    `db:"total_cost"`
	PaymentStatus bool       `db:"payment_status"`
	Rent          *user.Rent `db:"rent"`
	User          *user.User `db:"user"`
}

type Fine struct {
	ID          int64   `db:"id"`
	Sum         float64 `db:"sum"`
	Description string  `db:"description"`
}

type UserFines struct {
	ID     int64      `db:"id"`
	UserID int64      `db:"user_id"`
	FineID int64      `db:"fine_id"`
	Date   time.Time  `db:"date"`
	User   *user.User `db:"user"`
	Fine   *Fine      `db:"fine"`
}
