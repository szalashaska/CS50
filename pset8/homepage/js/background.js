if (typeof(Storage) !== "undefined") {
    if (localStorage.getItem("back_ground") == "dark") {
        var old_style = document.getElementById("style");
        old_style.href = "../css/dark.css";
    }
}

function change_color(cssFile) {
    var old_style = document.getElementById("style");
    old_style.href = cssFile;

    if (typeof(Storage) !== "undefined") {
        if (cssFile == "../css/dark.css") {
            localStorage.setItem("back_ground", "dark");
        }
        else {
            localStorage.setItem("back_ground", "light");
        }
    }
};