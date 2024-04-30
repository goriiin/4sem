package storage

import (
	"github.com/goriiin/cw/structures/user"
)

func (s *Storage) rentSelect() ([]user.Rent, error) {
	const op = "storage-rentSelect"
	return nil, nil
}

func (s *Storage) rentInsert(rent *user.Rent) error {
	const op = "storage-rentInsert"
	return nil
}
