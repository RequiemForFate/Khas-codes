// giving value to the time
const study_time = 25 * 60;
const break_time = 5 * 60;

// for character sprite gif
const gif_study = "";
const gif_break = "";
const gif_poked = "";

// dialogue for speech bubble
const dialouge_tier = {
    level1: ["Let's get to work.", "Focus.", "Hmph."],
    level3: ["Good job.", "See? I knew you can do it.", "I trust that you are following along?"],
    level5: ["You are catching up well.", "Well Done.", "You are improving well."]
};

// xp bar
let affection_xp = parseInt(localStorage.getItem('companionXP')) || 0;
let affection_level = parseInt(localStorage.getItem('companionLevel')) || 1;
const XP_per_Level = 10;

let timeLeft = study_time;
let timerId = null;
let isCurrentlyStudy = true;
let isPoked = false;

// ui elements
const timeDisplay = document.getElementById('time-display');
const statusLabel = document.getElementById('status-label');
const characterImg = document.getElementById('character-img');
const bubble = document.getElementById('speech-bubble');
const achievementBox = document.getElementById('achievement-box');

function updateTime() {
    const minutes = Math.floor(timeLeft / 60);
    const seconds = timeLeft % 60;
    if (timeDisplay) {
        timeDisplay.textContent = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
    }
}

function updateDisplay() {
    updateTime();
}

function updateStatusUI() {
    const levelXP = affection_xp % XP_per_Level;
    const percentage = (levelXP / XP_per_Level) * 100;

    const xpBarFill = document.getElementById('xp-bar-fill');
    const totalPointsText = document.getElementById('total-points-text');
    const levelBadge = document.getElementById('level-badge');

    if (xpBarFill) xpBarFill.style.width = `${percentage}%`;
    if (levelBadge) levelBadge.textContent = `Affection Lvl ${affection_level}`;
    if (totalPointsText) totalPointsText.textContent = `${levelXP} / ${XP_per_Level} XP (Total: ${affection_xp})`;

    checkMilestoneBadge();
}

function startTimer() {
    if (timerId !== null) return;
    timerId = setInterval(() => {
        timeLeft -= 1;
        updateDisplay();
        if (timeLeft <= 0) {
            clearInterval(timerId);
            timerId = null;
            switchMode();
        }
    }, 1000);
}

function pauseTimer() {
    if (timerId !== null) {
        clearInterval(timerId);
        timerId = null;
    }
}

function resetTimer() {
    pauseTimer();
    isCurrentlyStudy = true;
    timeLeft = study_time;
    if (statusLabel) statusLabel.textContent = "Ready to study.";
    if (gif_study && characterImg) characterImg.src = gif_study;
    updateDisplay();
    updateStatusUI();
}

function switchMode() {
    if (isCurrentlyStudy) {
        affection_xp += 2;
        const newLevel = Math.floor(affection_xp / XP_per_Level) + 1;
        if (newLevel > affection_level) {
            affection_level = newLevel;
            triggerAchievementNotification(`Level UP! Level ${affection_level} Unlocked!`);
        }
        localStorage.setItem('companionXP', affection_xp);
        localStorage.setItem('companionLevel', affection_level);
        updateStatusUI();

        isCurrentlyStudy = false;
        timeLeft = break_time;
        if (statusLabel) statusLabel.textContent = "Hard work deserves a break.";
        if (gif_break && characterImg) characterImg.src = gif_break;
    } else {
        isCurrentlyStudy = true;
        timeLeft = study_time;
        if (statusLabel) statusLabel.textContent = "Let's continue where we left off.";
        if (gif_study && characterImg) characterImg.src = gif_study;
    }
    updateDisplay();
    startTimer();
}

function pokeCharacter() {
    if (isPoked) return;
    isPoked = true;

    let dynamicPhrases = dialouge_tier.level1;
    if (affection_level >= 5) {
        dynamicPhrases = dialouge_tier.level5;
    } else if (affection_level >= 3) {
        dynamicPhrases = dialouge_tier.level3;
    }
    const randomIndex = Math.floor(Math.random() * dynamicPhrases.length);
    if (bubble) bubble.textContent = dynamicPhrases[randomIndex];
    if (bubble) bubble.classList.remove('hidden-bubble');
    if (gif_poked && characterImg) characterImg.src = gif_poked;

    setTimeout(() => {
        if (bubble) bubble.classList.add('hidden-bubble');
        if (characterImg) {
            if (isCurrentlyStudy && gif_study) {
                characterImg.src = gif_study;
            } else if (!isCurrentlyStudy && gif_break) {
                characterImg.src = gif_break;
            }
        }
        isPoked = false;
    }, 2000);
}

function triggerAchievementNotification(message) {
    if (!achievementBox) return;
    achievementBox.textContent = message;
    achievementBox.style.display = "block";
    setTimeout(() => {
        achievementBox.style.display = "none";
    }, 5000);
}

function checkMilestoneBadge() {
    if (affection_level === 3 && !localStorage.getItem('badge_lv3')) {
        localStorage.setItem('badge_lv3', 'true');
        triggerAchievementNotification("Achievement: Soften Heart");
    }
    if (affection_level === 5 && !localStorage.getItem('badge_lv5')) {
        localStorage.setItem('badge_lv5', 'true');
        triggerAchievementNotification("Achievement: Trusted Friend");
    }
}

function toggleMusicButtonText() {
    const toggleBtn = document.getElementById('toggle-music-btn');
    const musicPanel = document.getElementById('musicCollapse');
    if (!toggleBtn || !musicPanel) return;
    setTimeout(() => {
        if (musicPanel.classList.contains('show')) {
            toggleBtn.textContent = "Hide Music Panel";
        } else {
            toggleBtn.textContent = "Show Music Panel";
        }
    }, 50);
}

window.addEventListener('DOMContentLoaded', () => {
    updateDisplay();
    updateStatusUI();
    if (characterImg) characterImg.addEventListener('click', pokeCharacter);
    const toggleBtn = document.getElementById('toggle-music-btn');
    if (toggleBtn) toggleBtn.addEventListener('click', toggleMusicButtonText);
    const stopBtn = document.getElementById('stop-btn');
    if (stopBtn) stopBtn.addEventListener('click', resetTimer);
});