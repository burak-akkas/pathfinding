#pragma once
#include "Walker.h"
//#include <iostream>

enum Directions { DOWN, LEFT, RIGHT, UP, DOWNLEFT, DOWNRIGHT, UPLEFT, UPRIGHT };
const float PI = 3.14159265359f;

Walker::Walker(sf::Time frameTime, bool paused, bool looped, float x, float y) :
m_animation(NULL), m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused), m_isLooped(looped), m_texture(NULL)
{
	speed = 100.f;
	canMove = false;
	position.x = x;
	position.y = y;
	setPosition(position);
	loadTx();
}

void Walker::setAnimation(const Animation& animation)
{
	m_animation = &animation;
	m_texture = m_animation->getSpriteSheet();
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void Walker::setFrameTime(sf::Time time)
{
	m_frameTime = time;
}

void Walker::play()
{
	m_isPaused = false;
}

void Walker::play(const Animation& animation)
{
	if (getAnimation() != &animation)
		setAnimation(animation);
	play();
}

void Walker::pause()
{
	m_isPaused = true;
}

void Walker::stop()
{
	m_isPaused = true;
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void Walker::setLooped(bool looped)
{
	m_isLooped = looped;
}

void Walker::setColor(const sf::Color& color)
{
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;
}

const Animation* Walker::getAnimation() const
{
	return m_animation;
}

sf::FloatRect Walker::getLocalBounds() const
{
	sf::IntRect rect = m_animation->getFrame(m_currentFrame);

	float width = static_cast<float>(std::abs(rect.width));
	float height = static_cast<float>(std::abs(rect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect Walker::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

bool Walker::isLooped() const
{
	return m_isLooped;
}

bool Walker::isPlaying() const
{
	return !m_isPaused;
}

sf::Time Walker::getFrameTime() const
{
	return m_frameTime;
}

void Walker::setFrame(std::size_t newFrame, bool resetTime)
{
	if (m_animation)
	{
		sf::IntRect rect = m_animation->getFrame(newFrame);

		m_vertices[0].position = sf::Vector2f(0.f, 0.f);
		m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
		m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
		m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

		float left = static_cast<float>(rect.left) + 0.0001f;
		float right = left + static_cast<float>(rect.width);
		float top = static_cast<float>(rect.top);
		float bottom = top + static_cast<float>(rect.height);

		m_vertices[0].texCoords = sf::Vector2f(left, top);
		m_vertices[1].texCoords = sf::Vector2f(left, bottom);
		m_vertices[2].texCoords = sf::Vector2f(right, bottom);
		m_vertices[3].texCoords = sf::Vector2f(right, top);
	}

	if (resetTime)
		m_currentTime = sf::Time::Zero;
}

void Walker::move(float time) {
	if (canMove == true)
	{
		if (Util::distance(position, destination) > 5.f)
		{
			position += direction * speed * time;
			setPosition(position.x, position.y);
		}
		else if (path.size() > 0)
		{
			setDestination(&path.back());
			path.pop_back();
		}
		else
		{
			canMove = false;
		}
	}
}

void Walker::setDestination(sf::Vector2f *d) {
	destination = *d;
	direction = destination - position;
	direction = Util::normalize(direction);
	canMove = true;
}

void Walker::setPath(std::vector<sf::Vector2f> p) {
	resetDestination();
	path.clear();
	path = p;
	canMove = true;
}

void Walker::resetDestination() {
	destination = position;
}

bool Walker::isCanMove() {
	return canMove;
}

int Walker::whereToMove() {
	// test
	if (isCanMove()) {
		angle = atan2f(destination.y - position.y, destination.x - position.x);
		angle = (angle / PI * 180) + (angle > 0 ? 0 : 360);

		if (angle >= 80 && angle <= 100)
		{
			return DOWN;
		}
		else if (angle >= 170 && angle <= 190)
		{
			return LEFT;
		}
		else if (angle >= 260 && angle <= 280)
		{
			return UP;
		}
		else if (angle <= 350 && angle > 280)
		{
			return UPRIGHT;
		}
		else if (angle < 180 && angle > 90) {
			return DOWNLEFT;
		}
		else if (angle < 90 && angle > 0) {
			return DOWNRIGHT;
		}
		else if (angle < 270 && angle > 180) {
			return UPLEFT;
		}
		else
		{
			return RIGHT;
		}
	}
	else {
		return 0;
	}
	//# test
}

std::vector<Animation> Walker::loadAnimations() {
	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(96, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(128, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(160, 0, 32, 32));

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(96, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(128, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(160, 32, 32, 32));

	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(96, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(128, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(160, 64, 32, 32));

	Animation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(96, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(128, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(160, 96, 32, 32));

	Animation walkingAnimationDownLeft;
	walkingAnimationDownLeft.setSpriteSheet(texture);
	walkingAnimationDownLeft.addFrame(sf::IntRect(0, 128, 32, 32));
	walkingAnimationDownLeft.addFrame(sf::IntRect(32, 128, 32, 32));
	walkingAnimationDownLeft.addFrame(sf::IntRect(64, 128, 32, 32));
	walkingAnimationDownLeft.addFrame(sf::IntRect(96, 128, 32, 32));
	walkingAnimationDownLeft.addFrame(sf::IntRect(128, 128, 32, 32));
	walkingAnimationDownLeft.addFrame(sf::IntRect(160, 128, 32, 32));

	Animation walkingAnimationDownRight;
	walkingAnimationDownRight.setSpriteSheet(texture);
	walkingAnimationDownRight.addFrame(sf::IntRect(0, 160, 32, 32));
	walkingAnimationDownRight.addFrame(sf::IntRect(32, 160, 32, 32));
	walkingAnimationDownRight.addFrame(sf::IntRect(64, 160, 32, 32));
	walkingAnimationDownRight.addFrame(sf::IntRect(96, 160, 32, 32));
	walkingAnimationDownRight.addFrame(sf::IntRect(128, 160, 32, 32));
	walkingAnimationDownRight.addFrame(sf::IntRect(160, 160, 32, 32));

	Animation walkingAnimationUpLeft;
	walkingAnimationUpLeft.setSpriteSheet(texture);
	walkingAnimationUpLeft.addFrame(sf::IntRect(0, 192, 32, 32));
	walkingAnimationUpLeft.addFrame(sf::IntRect(32, 192, 32, 32));
	walkingAnimationUpLeft.addFrame(sf::IntRect(64, 192, 32, 32));
	walkingAnimationUpLeft.addFrame(sf::IntRect(96, 192, 32, 32));
	walkingAnimationUpLeft.addFrame(sf::IntRect(128, 192, 32, 32));
	walkingAnimationUpLeft.addFrame(sf::IntRect(160, 192, 32, 32));

	Animation walkingAnimationUpRight;
	walkingAnimationUpRight.setSpriteSheet(texture);
	walkingAnimationUpRight.addFrame(sf::IntRect(0, 224, 32, 32));
	walkingAnimationUpRight.addFrame(sf::IntRect(32, 224, 32, 32));
	walkingAnimationUpRight.addFrame(sf::IntRect(64, 224, 32, 32));
	walkingAnimationUpRight.addFrame(sf::IntRect(96, 224, 32, 32));
	walkingAnimationUpRight.addFrame(sf::IntRect(128, 224, 32, 32));
	walkingAnimationUpRight.addFrame(sf::IntRect(160, 224, 32, 32));

	std::vector<Animation> anims;
	anims.push_back(walkingAnimationDown);
	anims.push_back(walkingAnimationLeft);
	anims.push_back(walkingAnimationRight);
	anims.push_back(walkingAnimationUp);
	anims.push_back(walkingAnimationDownLeft);
	anims.push_back(walkingAnimationDownRight);
	anims.push_back(walkingAnimationUpLeft);
	anims.push_back(walkingAnimationUpRight);

	return anims;
}

void Walker::loadTx() {
	if (!texture.loadFromFile("./graphics/Player.png")) { // error 

	}
}

void Walker::update(sf::Time deltaTime)
{
	if (!m_isPaused && m_animation)
	{
		m_currentTime += deltaTime;

		if (m_currentTime >= m_frameTime)
		{
			m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());

			if (m_currentFrame + 1 < m_animation->getSize())
				m_currentFrame++;
			else
			{
				m_currentFrame = 0;

				if (!m_isLooped)
				{
					m_isPaused = true;
				}

			}
			setFrame(m_currentFrame, false);
		}
	}
}

void Walker::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_animation && m_texture)
	{
		states.transform *= getTransform();
		states.texture = m_texture;
		target.draw(m_vertices, 4, sf::Quads, states);
	}
}