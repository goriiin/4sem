package storage

import (
	"github.com/goriiin/cw/structures/user"
)

func (s *Storage) userSelect() ([]user.User, error) {
	const op = "storage-userSelect"
	return nil, nil
}

func (s *Storage) userInsert(user *user.User) error {
	const op = "storage-userInsert"
	return nil
}
