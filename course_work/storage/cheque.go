package storage

import (
	"github.com/goriiin/cw/structures/bank"
)

func (s *Storage) chequeSelect() ([]bank.Cheque, error) {
	const op = "storage-chequeSelect"

	return nil, nil
}

func (s *Storage) chequeInsert(cheque *bank.Cheque) error {
	const op = "storage-chequeInsert"
	return nil
}
