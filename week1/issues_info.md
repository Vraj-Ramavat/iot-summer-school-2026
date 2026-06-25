# Q6. GitHub Issues, Labels, and Milestones Documentation

To demonstrate proficiency in GitHub project management, three issues were created and tracked under the milestone **"Week 1 Completion"**.

---

## 1. Issue Database & Tracking

### Issue #1: [BUG] Blink interval not changing when potentiometer is at maximum
* **Type:** Bug
* **Labels:** `bug`, `high-priority`
* **Assignee:** Vraj-Ramavat
* **Milestone:** Week 1 Completion
* **Description:** 
  > When the potentiometer wiper is rotated to its maximum physical limit (mapping to 5V / raw analog reading `1023`), the LED remains in the last delay state instead of clamping to the minimum delay of 100ms. Investigation is needed to verify if the `map()` calculation or the pin read is saturating.
* **Resolution:** Closed by Commit `fix: resolve max potentiometer speed bug (Fixes #1)`.

### Issue #2: [FEATURE] Add RGB LED support
* **Type:** Feature Request
* **Labels:** `enhancement`, `good-first-issue`
* **Assignee:** Vraj-Ramavat
* **Milestone:** Week 1 Completion
* **Description:** 
  > Requesting support for common-cathode RGB LEDs. Implement three-channel digital or PWM writes to pins 9, 10, and 11 so that the status is color-coded:
  > - Red: Slow/Stopped
  > - Blue: Medium speed
  > - Green: Fast speed
  > This will provide better visual diagnostics.

### Issue #3: [ENHANCEMENT] Log data to Serial Monitor in CSV format
* **Type:** Enhancement
* **Labels:** `refactor`, `documentation`
* **Assignee:** Vraj-Ramavat
* **Milestone:** Week 1 Completion
* **Description:** 
  > Currently, the Serial Monitor output is unstructured text. We should refactor the logging statement to emit standard CSV data: `timestamp_ms,pot_value,delay_ms,blink_count`. This will allow students to copy the log into Excel or Python for plotting later.

---

## 2. Closing Issue with Commit Reference
The bug in **Issue #1** was resolved by adding a validation check to clamp the input range. 
The commit was pushed with the message:
`fix: clamp potentiometer map outputs to resolve speed bug (Fixes #1)`

This automatically linked the commit to the issue on GitHub and closed it.
