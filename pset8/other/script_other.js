function alert_button(event)
{
    var trigger = event.srcElement;
    alert('Misiek jesteś' + trigger.innerHTML);
}


let body = document.querySelector('body');
document.querySelector('#ala').onclick = function() {
body.style.backgroundColor = 'red';
}

let button = document.querySelector('#ala');
document.querySelector('#ala').onclick = function() {
button.style.backgroundColor = 'red';
}

let button = document.querySelector('button');
document.querySelector('#alpha').onclick = function() {
    button.style.backgroundColor = 'red';
}

let alpha = document.querySelector('#alpha');
alpha.onclick = function() {
alpha.style.backgroundColor = 'green';
};
let beta = document.getElementById('beta');
beta.onclick = function() {
beta.style.backgroundColor = 'red';
};
let charlie = document.getElementById('charlie');
charlie.onclick = function() {
charlie.style.backgroundColor = 'red';
};