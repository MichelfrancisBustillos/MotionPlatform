function updateSliderPWM(element) {
    var sliderValue = document.getElementById("y_slider").value;
    document.getElementById("y_slider_text").innerHTML = sliderValue;
    console.log(sliderValue);
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/slider?value="+sliderValue, true);
    xhr.send();
}