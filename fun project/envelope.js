'use strict';

document.addEventListener('DOMContentLoaded', () => {
    const envelope = document.getElementById('envelope');
    const envelopeTop = document.getElementById('envelopeTop');
    const letter = document.getElementById('contact');
    const left = document.getElementById('left');
    const bottomRight = document.getElementById('bottom-right');

    if (!envelope || !envelopeTop || !letter) return;

    // Ensure initial classes
    envelopeTop.classList.add('close');
    letter.classList.add('in');

    envelope.addEventListener('mouseover', openEnvelopeOnHover);
    envelope.addEventListener('mouseout', closeEnvelopeOnHover);

    function openEnvelopeOnHover() {
        envelopeTop.classList.remove('close');
        envelopeTop.classList.add('open');
        pullOutPartial();
    }

    function pullOutPartial() {
        letter.classList.remove('in');
        letter.classList.add('out-partial');
    }

    function closeEnvelopeOnHover() {
        putIn();
        envelopeTop.classList.add('close');
        envelopeTop.classList.remove('open');
    }

    function putIn() {
        letter.classList.remove('out-partial');
        letter.classList.add('in');
    }
});