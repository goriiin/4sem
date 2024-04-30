package storage

import (
	"github.com/goriiin/cw/structures/transport"
)

func (s *Storage) transportInfoSelect() ([]transport.Info, error) {
	const op = "storage-transportInfoSelect"
	return nil, nil
}

func (s *Storage) transportInfoInsert(transportInfo *transport.Info) error {
	const op = "storage-transportInfoInsert"
	return nil
}
