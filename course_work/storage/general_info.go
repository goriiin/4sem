package storage

import (
	"github.com/goriiin/cw/structures/transport"
)

func (s *Storage) generalInfoSelect() ([]transport.GeneralInfo, error) {
	const op = "storage-generalInfoSelect"
	return nil, nil
}

func (s *Storage) generalInfoInsert(info *transport.GeneralInfo) error {
	const op = "storage-generalInfoInsert"
	return nil
}
