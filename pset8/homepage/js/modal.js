document.addEventListener("DOMContentLoaded", modal(event));

function modal(event) {
    var modal = document.getElementById("my_modal");
    var img = document.getElementById("my_image");
    var img_modal = document.getElementById("modal_image");
    var caption_txt = document.getElementById("caption");

    img.onclick = function() {
        modal.style.display = "block";
        img_modal.src = this.src;
        caption_txt.innerHTML = this.alt;
        };

    var close = document.getElementsByClassName("close_btn")[0];
    close.onclick = function() {
        modal.style.display = "none";
    };
}
