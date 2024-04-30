package storage

import (
	"github.com/goriiin/cw/structures/user"
)

func (s *Storage) driverLicenceSelect() ([]user.DriverLicense, error) {
	const op = "storage-driverLicenceSelect"
	return nil, nil
}

func (s *Storage) driverLicenceInsert(license *user.DriverLicense) error {
	const op = "storage-driverLicenceInsert"
	return nil
}
