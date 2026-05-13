'use strict';
(function() {
    var envelope = document.getElementById('envelope');
    var envelopeTop = document.getElementById('envelopeTop');
    var letter = document.getElementById('contact');
    var left = document.getElementById('left');
    var bottomRight = document.getElementById('bottom-right');
})();

envelopeTop.classList.add("close");

envelope.addEventListener('mouseover', openEnvelopeOnHover);
envelope.addEventListener('mouseout', closeEnvelopeOnHover);

function openEnvelopeOnHover() {
    envelopeTop.classList.remove("close");
    envelopeTop.classList.remove("open");
    pullOutPartial();
}

function pullOutPartial() {
    letter.classList.remove("in");
    letter.classList.add("out-partial");
}

function closeEnvelopeOnHover() {
    if (flag === 1) {
        putIn();
        envelopeTop.classList.add("close");
        envelopeTop.classList.remove("open");
    } else {
        envelope.removeEventListener('mouiseout', closeEnvelopeOnHover);
    }
}

function putIn() {
    letter.classList.remove("out-partial");
    letter.classList.add("in")
}