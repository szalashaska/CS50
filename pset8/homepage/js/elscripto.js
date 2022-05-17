window.onscroll = function() {
    var colors = document.getElementById("colors");
    var freeze = colors.offsetTop;
    if (window.pageYOffset > freeze && $(window).width() > 800) {
        colors.classList.add("freeze_color_switch");
    }
    else {
        colors.classList.remove("freeze_color_switch");
    }
};

function my_alert() {
    let name = document.querySelector("#fname").value;
    let last_name = document.querySelector("#lname").value;
    if (name != "" || last_name != "") {
        alert("Hello " + name + last_name + " ! Your form was successfully submitted!");
    }
    else {
        alert("Hello stranger! Your form was successfully submitted!");
    }
}

/*
function change_color(cssFile) {
    var old_style = document.getElementById("style");
    old_style.href = cssFile;
}
*/