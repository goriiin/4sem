const gameContainer = document.getElementById('game-container');
const resultElement = document.getElementById('result');
const playWithPcButton = document.getElementById('play-with-pc');
const playWithFriendButton = document.getElementById('play-with-friend');

var game_result = {
  'rock' : 'камень',
  'scissors' : 'ножницы',
  'paper' : 'бумага'
};

let gameMode = null;
let player1Choice = null;
let player2Choice = null;

playWithPcButton.addEventListener('click', () => {
  gameMode = 'pc';
  gameContainer.style.display = 'flex';
});

playWithFriendButton.addEventListener('click', () => {
  gameMode = 'friend';
  gameContainer.style.display = 'flex';
});

gameContainer.addEventListener('click', (event) => {
  if (event.target.classList.contains('choice')) {
    if (gameMode === 'pc') {
      player1Choice = event.target.id;
      computerChoice = getComputerChoice();
      playRound();
    } else if (gameMode === 'friend') {
      if (!player1Choice) {
        player1Choice = event.target.id;
        alert('Ожидаем выбора второго игрока...');
      } else {
        player2Choice = event.target.id;
        playRoundWithFriend();
      }
    }
  }
});

function getComputerChoice() {
  const choices = ['rock', 'scissors', 'paper'];
  return choices[Math.floor(Math.random() * choices.length)];
}

function playRound() {
  let result = '';
  if (player1Choice === computerChoice) {
    result = 'Ничья!';
  } else if ((player1Choice === 'rock' && computerChoice === 'scissors') ||
             (player1Choice === 'scissors' && computerChoice === 'paper') ||
             (player1Choice === 'paper' && computerChoice === 'rock')) {
    result = 'Вы выиграли!';
  } else {
    result = 'ПК выиграл!';
  }
  resultElement.textContent = `Вы выбрали: ${game_result[player1Choice]}, ПК выбрал: ${game_result[computerChoice]}. ${result}`;
}

function playRoundWithFriend() {
  let result = '';
  if (player1Choice === player2Choice) {
    result = 'Ничья!';
  } else if ((player1Choice === 'rock' && player2Choice === 'scissors') ||
             (player1Choice === 'scissors' && player2Choice === 'paper') ||
             (player1Choice === 'paper' && player2Choice === 'rock')) {
    result = 'Первый игрок выиграл!';
  } else {
    result = 'Второй игрок выиграл!';
  }
  resultElement.textContent = `Первый игрок выбрал: ${game_result[player1Choice]}, Второй игрок выбрал: ${game_result[player2Choice]}. ${result}`;
}
