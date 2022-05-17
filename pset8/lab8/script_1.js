document.addEventListener('DOMContentLoaded', function() {
    let correct = document.querySelector('.correct');
    correct.addEventListener('click', function(){
        correct.style.backgroundColor = 'green';
        document.querySelector('#text').innerHTML = 'Correct!';
    });
    let incorrect = document.querySelectorAll('.incorrect');
        for (let i = 0; i < incorrect.length; i++){
            incorrect[i].addEventListener('click', function() {
                incorrect[i].style.backgroundColor = 'red';
                document.querySelector('#text').innerHTML = 'Incorrect';
            } );
        }
    document.querySelector('#check').addEventListener('click', function() {
        let letters = document.querySelector('#letters');
        if (letters.value == 'Always'){
            letters.style.backgroundColor = 'green';
            document.querySelector('#answer').innerHTML = 'Correct!';
        }
        else {
            letters.style.backgroundColor = 'red';
            document.querySelector('#answer').innerHTML = 'Incorrect';
        }
    });
});