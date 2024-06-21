let timer;
let start = 0;
let hours = 0;
let minutes = 0;
let seconds = 0;
let cs = 0;

function startStopwatch() { 
    if (!start) {
        timer = setInterval(displayStopwatch, 10);    
        start = 1;
    }
    else {
        clearInterval(timer);   
        start = 0;
    }
    document.getElementById("startButton").innerHTML = start ? "Pause" : "Start";
}


function displayStopwatch() {
  cs++;

  if (cs == 100) {
    seconds++;  
    cs = 0;  
    if (seconds === 60) {
        seconds = 0;
        minutes++;
        if (minutes === 60) {
            minutes = 0;
            hours++;
        }
    }    
  }

  let displayHours = hours < 10 ? "0" + hours : hours;
  let displayMinutes = minutes < 10 ? "0" + minutes : minutes;
  let displaySeconds = seconds < 10 ? "0" + seconds : seconds;
  let displaycSeconds = cs < 10 ? "0" + cs : cs;

  document.getElementById("display").innerText = `${displayHours}:${displayMinutes}:${displaySeconds}:${displaycSeconds}`;
}

function resetStopwatch() {
  clearInterval(timer);
  hours = 0;
  minutes = 0;
  seconds = 0;
  document.getElementById("display").innerText = "00:00:00:00";
  document.getElementById("startButton").disabled = false;
}