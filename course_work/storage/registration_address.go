package storage

import (
	"github.com/goriiin/cw/structures/user"
)

func (s *Storage) registrationAddressSelect() ([]user.RegistrationAddress, error) {
	const op = "storage-registrationAddressSelect"
	return nil, nil

}

func (s *Storage) registrationAddressInsert(address *user.RegistrationAddress) error {
	const op = "storage-registrationAddressInsert"
	return nil
}
