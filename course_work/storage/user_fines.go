package storage

import (
	"github.com/goriiin/cw/structures/bank"
)

func (s *Storage) userFinesSelect() ([]bank.UserFines, error) {
	const op = "storage-userFinesSelect"
	return nil, nil
}

func (s *Storage) userFinesInsert(uf *bank.UserFines) error {
	const op = "storage-userFinesInsert"
	return nil
}
