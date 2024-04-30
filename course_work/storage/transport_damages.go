package storage

import (
	"github.com/goriiin/cw/structures/transport"
)

func (s *Storage) transportDamagesSelect() ([]transport.Damages, error) {
	const op = "storage-transportDamagesSelect"
	return nil, nil
}

func (s *Storage) transportDamageInsert(transportDamages *transport.Damages) error {
	const op = "storage-transportDamageInsert"
	return nil
}
