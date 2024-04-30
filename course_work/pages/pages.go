package pages

import (
	"github.com/goriiin/cw/storage"
	"github.com/goriiin/cw/structures/bank"
	"github.com/goriiin/cw/structures/transport"
	"github.com/goriiin/cw/structures/user"
)

type BasePage struct {
	Content string
	Fields  []string
	Data    interface{}
}

func initBasePage() BasePage {
	return BasePage{
		Content: "КУРСОВАЯ РАБОТА -- ВЫПОЛНИЛ КОШЕНКОВ Д.О",
	}
}

type BankData struct {
	Content string
	Fields  []string
	Data    []user.BankData
}

func initBankData(s *storage.Storage) (BankData, error) {
	data, err := s.BankDataSelect()
	if err != nil {
		return BankData{}, err
	}

	return BankData{
		Content: "Банковская информация",
		Fields:  []string{"id", "num", "cvc", "date"},
		Data:    data,
	}, nil
}

type Cheque struct {
	Content string
	Fields  []string
	Data    []bank.Cheque
}

func initCheque(s *storage.Storage) (Cheque, error) {
	data, err := s.ChequeSelect()
	if err != nil {
		return Cheque{}, err
	}
	return Cheque{
		Content: "Чеки",
		Fields:  []string{"id", "rent_id", "user_id", "total_cost", "payment_status"},
		Data:    data,
	}, nil
}

type Damage struct {
	Content string
	Fields  []string
	Data    []transport.Damage
}

func initDamage(s *storage.Storage) (Damage, error) {
	data, err := s.DamageSelect()
	if err != nil {
		return Damage{}, err
	}
	return Damage{
		Content: "Виды Урона",
		Data:    data,
		Fields:  []string{},
	}, nil
}

type DriverLicense struct {
	Content string
	Fields  []string
	Data    []user.DriverLicense
}

func initDriverLicense(s *storage.Storage) (DriverLicense, error) {
	data, err := s.DriverLicenceSelect()
	if err != nil {
		return DriverLicense{}, err
	}
	return DriverLicense{
		Content: "Водительские права",
		Data:    data,
		Fields:  []string{},
	}, nil
}

type Fine struct {
	Content string
	Fields  []string
	Data    []bank.Fine
}

func initFine(s *storage.Storage) (Fine, error) {
	data, err := s.FineSelect()
	if err != nil {
		return Fine{}, err
	}
	return Fine{
		Content: "Штрафы",
		Data:    data,
		Fields:  []string{},
	}, nil
}

type GeneralInfo struct {
	Content string
	Fields  []string
	Data    []transport.GeneralInfo
}

func initGeneralInfo(s *storage.Storage) (GeneralInfo, error) {
	data, err := s.GeneralInfoSelect()
	if err != nil {
		return GeneralInfo{}, err
	}
	return GeneralInfo{
		Content: "Общая информация о машине",
		Fields:  []string{},
		Data:    data,
	}, nil
}

type Human struct {
	Content string
	Fields  []string
	Data    []user.Human
}

func initHuman(s *storage.Storage) (Human, error) {
	data, err := s.HumanSelect()
	if err != nil {
		return Human{}, err
	}
	return Human{
		Content: "Информация о человеке",
		Data:    data,
		Fields:  []string{},
	}, nil
}

type RegistrationAddress struct {
	Content string
	Fields  []string
	Data    []user.RegistrationAddress
}

func initRegistrationAddress(s *storage.Storage) (RegistrationAddress, error) {
	data, err := s.RegistrationAddressSelect()
	if err != nil {
		return RegistrationAddress{}, err
	}
	return RegistrationAddress{
		Content: "Адрес регистрации",
		Data:    data,
		Fields:  []string{},
	}, nil
}

type Rent struct {
	Content string
	Fields  []string
	Data    []user.Rent
}

func initRent(s *storage.Storage) (Rent, error) {
	data, err := s.RentSelect()
	if err != nil {
		return Rent{}, err
	}
	return Rent{
		Content: "Аренда",
		Data:    data,
		Fields:  []string{},
	}, err
}

type Transport struct {
	Content string
	Fields  []string
	Data    []transport.Transport
}

func initTransport(s *storage.Storage) (Transport, error) {
	data, err := s.TransportSelect()
	if err != nil {
		return Transport{}, err
	}
	return Transport{
		Content: "Транспорт",
		Data:    data,
		Fields:  []string{},
	}, err
}
