#include <stdio.h>
#include "raylib.h"
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_WIDTH 800
#define BOARD_HEIGHT 700
#define BOARD_OFFSET 10
#define CELL_WIDTH (BOARD_WIDTH / 3)
#define CELL_HEIGHT (BOARD_HEIGHT / 3)
#define MARK_OFFSET 50
#define COLS 3
#define ROWS 3
#define CIRCLE_RADIUS 80 

void draw_board(char board[COLS][ROWS])
{
	// Vertical lines
	DrawLine(BOARD_WIDTH / 3, BOARD_OFFSET, BOARD_WIDTH / 3, BOARD_HEIGHT - BOARD_OFFSET, BLACK);
	DrawLine(BOARD_WIDTH - (BOARD_WIDTH / 3), BOARD_OFFSET, BOARD_WIDTH - (BOARD_WIDTH / 3), BOARD_HEIGHT - BOARD_OFFSET, BLACK);

	// Horizontal lines
	DrawLine(BOARD_OFFSET, (BOARD_HEIGHT / 3), BOARD_WIDTH - BOARD_OFFSET, (BOARD_HEIGHT / 3), BLACK);
	DrawLine(BOARD_OFFSET, BOARD_HEIGHT - (BOARD_HEIGHT / 3), BOARD_WIDTH - BOARD_OFFSET, BOARD_HEIGHT - (BOARD_HEIGHT / 3), BLACK);

	for (int i = 0; i < COLS; ++i) {
		for (int j = 0; j < ROWS; ++j) {
			if(board[i][j] == 'X') {
				DrawLine(MARK_OFFSET + (j * CELL_WIDTH), BOARD_OFFSET + MARK_OFFSET + (i * CELL_HEIGHT), CELL_WIDTH - MARK_OFFSET + (j * CELL_WIDTH), CELL_HEIGHT - MARK_OFFSET + (i * CELL_HEIGHT), BLACK);
				DrawLine(CELL_WIDTH - MARK_OFFSET + (j * CELL_WIDTH), BOARD_OFFSET + MARK_OFFSET + (i * CELL_HEIGHT), MARK_OFFSET + (j * CELL_WIDTH), CELL_HEIGHT - MARK_OFFSET + (i * CELL_HEIGHT), BLACK);
			} else if(board[i][j] == 'O') {
				DrawCircleLines((CELL_WIDTH / 2) + (j * CELL_WIDTH), (CELL_HEIGHT / 2) + (i * CELL_HEIGHT), CIRCLE_RADIUS, BLACK);
			}
		}
	}
}

bool mouse_clicked(char board[COLS][ROWS], Vector2 mouse_position, char mark)
{
	// First row
	if(mouse_position.x < CELL_WIDTH && mouse_position.y < CELL_HEIGHT && board[0][0] == '0') board[0][0] = mark;
	else if(mouse_position.x < 2 * CELL_WIDTH && mouse_position.x > CELL_WIDTH && mouse_position.y < CELL_HEIGHT && board[0][1] == '0') board[0][1] = mark;
	else if(mouse_position.x < 3 * CELL_WIDTH && mouse_position.x > 2 * CELL_WIDTH && mouse_position.y < CELL_HEIGHT && board[0][2] == '0') board[0][2] = mark;
	
	// Second row
	else if(mouse_position.x < CELL_WIDTH && mouse_position.y > CELL_HEIGHT && mouse_position.y < 2 * CELL_HEIGHT && board[1][0] == '0') board[1][0] = mark;
	else if(mouse_position.x < 2 * CELL_WIDTH && mouse_position.x > CELL_WIDTH  && mouse_position.y > CELL_HEIGHT && mouse_position.y < 2 * CELL_HEIGHT && board[1][1] == '0') board[1][1] = mark;
	else if(mouse_position.x < 3 * CELL_WIDTH && mouse_position.x > 2 * CELL_WIDTH  && mouse_position.y > CELL_HEIGHT && mouse_position.y < 2 * CELL_HEIGHT && board[1][2] == '0') board[1][2] = mark;
	
	// Third row
	else if(mouse_position.x < CELL_WIDTH && mouse_position.y > 2 * CELL_HEIGHT && board[2][0] == '0') board[2][0] = mark;
	else if(mouse_position.x < 2 * CELL_WIDTH && mouse_position.x > CELL_WIDTH  && mouse_position.y > 2 * CELL_HEIGHT && board[2][1] == '0') board[2][1] = mark;
	else if(mouse_position.x < 3 * CELL_WIDTH && mouse_position.x > 2 * CELL_WIDTH  && mouse_position.y > 2 * CELL_HEIGHT && board[2][2] == '0') board[2][2] = mark;

	// If cell can't be played
	else return false;
	
	return true;
}

int check_winner(char board[COLS][ROWS])
{
	// Horizontal check
	//
	if(board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != '0') return 1;
	else if(board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != '0') return 1;
	else if(board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != '0') return 1;

	// Vertical check
	//
	else if(board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != '0') return 1;
	else if(board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != '0') return 1;
	else if(board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != '0') return 1;

	// Diagonal check
	//
	else if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '0') return 1;
	else if(board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != '0') return 1;
	
	else {
		int cpt = 0;
		for (int i = 0; i < COLS; ++i) {
			for (int j = 0; j < ROWS; ++j) {
				if(board[i][j] != '0') ++cpt;
			}
		}
		if(cpt == ROWS * COLS) return -1;
	}

	return 0;
}

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe");
	char board[COLS][ROWS] = {
		{'0', '0', '0'},
		{'0', '0', '0'},
		{'0', '0', '0'}
	};
	int game_finished = 0;
	char turn = 'X';
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_board(board);
		switch (game_finished) {
			case 0:
				if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
					Vector2 mouse_position = GetMousePosition();
					if(mouse_clicked(board, mouse_position, turn)) turn = turn == 'X' ? 'O' : 'X';
				}
				DrawText(turn == 'X' ? "X to play" : "O to play", SCREEN_WIDTH / 3 + 50, SCREEN_HEIGHT - 50, 30, BLACK);
				break;
			case 1:
				DrawText(turn == 'O' ? "X Won!" : "O Won!", SCREEN_WIDTH / 3 + 80, SCREEN_HEIGHT - 50, 30, BLACK);
				break;
			case -1:
				DrawText("Tie!", SCREEN_WIDTH / 3 + 100, SCREEN_HEIGHT - 50, 30, BLACK);
				break;
			default:
				break;
		};
		game_finished = check_winner(board);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
