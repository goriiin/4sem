package storage

import (
	"context"
	"fmt"
	"github.com/goriiin/cw/config"
	"github.com/goriiin/cw/structures/bank"
	"github.com/goriiin/cw/structures/transport"
	"github.com/goriiin/cw/structures/user"
	"github.com/jackc/pgx/v5/pgxpool"
	"os"
)

type Storage struct {
	db *pgxpool.Pool
}

// New -
func New(pathToDB string) (*Storage, error) {
	const op = "db.postgres.New"

	cfg, err := config.ReadConfig(pathToDB)
	if err != nil {
		fmt.Println(fmt.Errorf("%s - config err: %w\n", op, err))
		os.Exit(1)
	}

	poolConfig, err := config.NewPoolConfig(cfg)
	if err != nil {
		fmt.Println(fmt.Errorf("%s - config err: %w\n", op, err))
		os.Exit(1)
	}

	poolConfig.MaxConns = 5

	conn, err := config.NewConnection(poolConfig)
	if err != nil {
		return nil, fmt.Errorf("%s: %w", op, err)
	}

	return &Storage{
		db: conn,
	}, nil
}

// TestSelect - вывод в консоль всех таблиц
func (s *Storage) TestSelect() error {
	const op = "db.postgres.TestSelect"

	rows, err := s.db.Query(context.Background(),
		`SELECT table_name
             FROM information_schema.tables 
             WHERE table_schema = 'public';`)

	if err != nil {
		return fmt.Errorf("%s - config err: %w", op, err)
	}

	for rows.Next() {
		var tableName string
		err = rows.Scan(&tableName)
		if err != nil {
			return fmt.Errorf("%s - config err: %w", op, err)
		}
		fmt.Printf("Created table name: %s\n", tableName)
	}

	// проверяем ошибку после обработки результатов
	if err = rows.Err(); err != nil {
		return fmt.Errorf("%s: %w", op, err)
	}
	return nil
}

func (s *Storage) HumanSelect() ([]user.Human, error) {
	const op = "storage-humanSelect"
	return nil, nil
}
func (s *Storage) GeneralInfoSelect() ([]transport.GeneralInfo, error) {
	const op = "storage-generalInfoSelect"
	return nil, nil
}

func (s *Storage) FineSelect() ([]bank.Fine, error) {
	const op = "storage-fineSelect"
	return nil, nil
}

func (s *Storage) DriverLicenceSelect() ([]user.DriverLicense, error) {
	const op = "storage-driverLicenceSelect"
	return nil, nil
}

func (s *Storage) DamageSelect() ([]transport.Damage, error) {
	const op = "storage-damageSelect"
	return nil, nil
}

func (s *Storage) ChequeSelect() ([]bank.Cheque, error) {
	const op = "storage-chequeSelect"

	return nil, nil
}

func (s *Storage) BankDataSelect() ([]user.BankData, error) {
	const op = "storage-bankDataSelect"

	return nil, nil
}

func (s *Storage) RegistrationAddressSelect() ([]user.RegistrationAddress, error) {
	const op = "storage-registrationAddressSelect"
	return nil, nil

}

func (s *Storage) RentSelect() ([]user.Rent, error) {
	const op = "storage-rentSelect"
	return nil, nil
}

func (s *Storage) TransportSelect() ([]transport.Transport, error) {
	const op = "storage-transportSelect"
	return nil, nil
}

func (s *Storage) TransportDamagesSelect() ([]transport.Damages, error) {
	const op = "storage-transportDamagesSelect"
	return nil, nil
}

func (s *Storage) TransportInfoSelect() ([]transport.Info, error) {
	const op = "storage-transportInfoSelect"
	return nil, nil
}

func (s *Storage) UserSelect() ([]user.User, error) {
	const op = "storage-userSelect"
	return nil, nil
}

func (s *Storage) UserLicenceSelect() ([]user.License, error) {
	const op = "storage-userLicSelect"
	return nil, nil
}

func (s *Storage) UserFinesSelect() ([]bank.UserFines, error) {
	const op = "storage-userFinesSelect"
	return nil, nil
}
