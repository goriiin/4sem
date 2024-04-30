package storage

import (
	"github.com/goriiin/cw/structures/bank"
)

func (s *Storage) bankDataSelect() ([]bank.Data, error) {
	const op = "storage-bankDataSelect"

	return nil, nil
}

func (s *Storage) bankDataInsert(data *bank.Data) {
	const op = "storage-bankDataInsert"
}
