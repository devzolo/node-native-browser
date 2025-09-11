import assert from "node:assert";
import { describe, it } from "node:test";
import { eKeyEventType, NativeBrowser } from "../index.ts";

describe("Browser Test", () => {
	it("should load the module without errors", () => {
		try {
			console.log("Module loaded successfully:", Object.keys(NativeBrowser));

			// Test that the module exports exist
			assert.ok(NativeBrowser, "NativeBrowser should be defined");
			assert.ok(eKeyEventType, "eKeyEventType should be defined");

			// Test enum values
			assert.strictEqual(eKeyEventType.KEYEVENT_RAWKEYDOWN, 0);
			assert.strictEqual(eKeyEventType.KEYEVENT_KEYDOWN, 1);
			assert.strictEqual(eKeyEventType.KEYEVENT_KEYUP, 2);
			assert.strictEqual(eKeyEventType.KEYEVENT_CHAR, 3);
		} catch (error) {
			console.error("Error loading module:", error);
			throw error;
		}
	});
});
