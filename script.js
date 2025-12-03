const TOTAL_BLOCKS = 256;
let diskState = [];

function initDisk() {
  diskState = Array(TOTAL_BLOCKS).fill('healthy');
  for (let i = 30; i < 50; i++) diskState[i] = 'fragmented';
  renderDisk();
  updateStats();
  document.getElementById('log').textContent = '📁 File system loaded. Ready for simulation!';
}

function renderDisk() {
  const diskEl = document.getElementById('disk');
  diskEl.innerHTML = '';
  diskState.forEach((state, i) => {
    const block = document.createElement('div');
    block.className = `block ${state}`;
    if (state === 'recovered') {
      const check = document.createElement('div');
      check.textContent = '✓';
      check.style.position = 'absolute';
      check.style.top = '50%';
      check.style.left = '50%';
      check.style.transform = 'translate(-50%, -50%)';
      check.style.color = 'white';
      check.style.fontSize = '14px';
      check.style.fontWeight = 'bold';
      check.style.textShadow = '0 0 4px rgba(0,0,0,0.8)';
      block.appendChild(check);
    }
    diskEl.appendChild(block);
  });
}

function updateStats() {
  const healthy = diskState.filter(s => s === 'healthy').length;
  const deleted = diskState.filter(s => s === 'deleted').length;
  const corrupted = diskState.filter(s => s === 'corrupted').length;
  const frag = Math.round((diskState.filter(s => s === 'fragmented').length / TOTAL_BLOCKS) * 100);

  document.getElementById('healthyCount').textContent = healthy;
  document.getElementById('deletedCount').textContent = deleted;
  document.getElementById('corruptedCount').textContent = corrupted;
  document.getElementById('fragLevel').textContent = frag + '%';
}

function setLog(message) {
  document.getElementById('log').textContent = message;
}

function showModal() {
  document.getElementById('successModal').classList.add('active');
}

function closeModal() {
  document.getElementById('successModal').classList.remove('active');
}

function simulateDeletion() {
  let count = 0;
  for (let i = 0; i < 25; i++) {
    const idx = Math.floor(Math.random() * TOTAL_BLOCKS);
    if (diskState[idx] === 'healthy' || diskState[idx] === 'fragmented') {
      diskState[idx] = 'deleted';
      count++;
    }
  }
  renderDisk();
  updateStats();
  setLog(`🗑️ Deleted ${count} file blocks.`);
}

function simulateCorruption() {
  let count = 0;
  for (let i = 0; i < 15; i++) {
    const idx = Math.floor(Math.random() * TOTAL_BLOCKS);
    if (diskState[idx] !== 'corrupted' && diskState[idx] !== 'deleted') {
      diskState[idx] = 'corrupted';
      count++;
    }
  }
  renderDisk();
  updateStats();
  setLog(`💥 Corrupted ${count} blocks.`);
}

function recoverFiles() {
  const recoverableIndices = [];
  for (let i = 0; i < diskState.length; i++) {
    if (diskState[i] === 'deleted' || diskState[i] === 'corrupted') {
      recoverableIndices.push(i);
    }
  }

  if (recoverableIndices.length === 0) {
    setLog("ℹ️ No recoverable files found!");
    return;
  }

  recoverableIndices.forEach(i => diskState[i] = 'recovered');
  renderDisk();
  setLog(`✅ Recovering ${recoverableIndices.length} files...`);

  setTimeout(() => {
    recoverableIndices.forEach(i => diskState[i] = 'healthy');
    renderDisk();
    updateStats();
    setLog(`🎉 Successfully recovered ${recoverableIndices.length} file blocks!`);

    // ✅ Check if ALL deleted & corrupted are gone → show popup!
    const stillDeleted = diskState.some(s => s === 'deleted' || s === 'corrupted');
    if (!stillDeleted) {
      setTimeout(showModal, 800); // slight delay for effect
    }
  }, 1800);
}

function defrag() {
  let count = 0;
  for (let i = 0; i < diskState.length; i++) {
    if (diskState[i] === 'fragmented') {
      diskState[i] = 'healthy';
      count++;
    }
  }
  renderDisk();
  updateStats();
  setLog(`⚡ Defragmented ${count} blocks. Performance optimized!`);
}

window.onload = initDisk;
