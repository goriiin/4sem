package storage

import (
	"github.com/goriiin/cw/structures/user"
)

func (s *Storage) userLicenceSelect() ([]user.License, error) {
	const op = "storage-userLicSelect"
	return nil, nil
}

func (s *Storage) userLicenceInsert(license *user.License) error {
	const op = "storage-userLicInsert"
	return nil
}
