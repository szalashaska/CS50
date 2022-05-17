function first_question(event)
{
    let button = event.srcElement;
    let text = document.querySelector('#text');

    if (button.id == 'alpha'){
        button.style.backgroundColor = 'green';
        text.innerHTML = 'Correct!';
    }
    else {
        button.style.backgroundColor = 'red';
        text.innerHTML = 'Incorrect';
    }
}

function secound_question(event)
{
    let text = document.querySelector('#answer');
    let input = document.querySelector('#letters');
    if (input.value.toUpperCase() == 'ALWAYS'){
        input.style.backgroundColor = 'green';
        text.innerHTML = 'Correct!';
    }
    else {
        input.style.backgroundColor = 'red';
        text.innerHTML = 'Incorrect';
    }
}