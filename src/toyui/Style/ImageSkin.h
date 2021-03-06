//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_IMAGESKIN_H
#define TOY_IMAGESKIN_H

/* toy */
#include <toyobj/Object.h>
#include <toyobj/Indexer.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/GlobalType.h>
#include <toyobj/Util/Colour.h>
#include <toyui/Forward.h>
#include <toyui/Style/Dim.h>
#include <toyui/Image.h>

/* std */
#include <vector>
#include <functional>

namespace toy
{
	class _I_ ImageSkin : public Struct
	{
	public:
		enum Section
		{
			TOP_LEFT = 0, // Corners
			TOP_RIGHT = 1,
			BOTTOM_RIGHT = 2,
			BOTTOM_LEFT = 3,
			TOP = 4, // Borders
			RIGHT = 5,
			BOTTOM = 6,
			LEFT = 7,
			FILL = 8 // Fill
		};

	public:
		ImageSkin(Image& image, int left, int top, int right, int bottom, int margin = 0, Dimension stretch = DIM_NULL)
			: d_image(&image)
			, d_top(top), d_right(right), d_bottom(bottom), d_left(left)
			, d_margin(margin)
			, d_stretch(stretch)
			, d_images(9)
			, d_prepared(false)
		{
			this->setupImage(*d_image);
		}

		ImageSkin()
			: d_image(nullptr)
		{}

		bool null() const { return d_image == nullptr; }

		void setupImage(Image& image)
		{
			d_image = &image;
			d_images[TOP_LEFT].d_name = image.d_name + "_topleft";
			d_images[TOP_RIGHT].d_name = image.d_name + "_topright";
			d_images[BOTTOM_RIGHT].d_name = image.d_name + "_bottomright";
			d_images[BOTTOM_LEFT].d_name = image.d_name + "_bottomleft";

			d_images[TOP].d_name = image.d_name + "_top";
			d_images[RIGHT].d_name = image.d_name + "_right";
			d_images[BOTTOM].d_name = image.d_name + "_bottom";
			d_images[LEFT].d_name = image.d_name + "_left";

			d_images[FILL].d_name = image.d_name + "_fill";

			for(size_t i = 0; i < 9; ++i)
			{
				d_images[i].d_index = d_image->d_index;
				d_images[i].d_atlas = d_image->d_atlas;
			}

			this->setupSize(image.d_width, image.d_height);
		}

		void setupSize(int width, int height)
		{
			d_width = width;
			d_height = height;
			d_fillWidth = width - d_left - d_right;
			d_fillHeight = height - d_top - d_bottom;

			d_solidWidth = width - d_margin - d_margin;
			d_solidHeight = height - d_margin - d_margin;

			this->stretchCoords(0, 0, width, height, [this](Section s, const BoxFloat& rect) {
				this->d_images[s].d_left = this->d_image->d_left + int(rect.x());
				this->d_images[s].d_top = this->d_image->d_top + int(rect.y());
				this->d_images[s].d_width = int(rect.w());
				this->d_images[s].d_height = int(rect.h());
			 });
		}

		void stretchCoords(int x, int y, int width, int height, std::function<void(Section, const BoxFloat&)> filler) const
		{
			int fillWidth = width - d_left - d_right;
			int fillHeight = height - d_top - d_bottom;

			filler(TOP_LEFT, BoxFloat(x, y, d_left, d_top));
			filler(TOP_RIGHT, BoxFloat(x + fillWidth + d_left, y, d_right, d_top));
			filler(BOTTOM_RIGHT, BoxFloat(x + fillWidth + d_left, y + fillHeight + d_top, d_right, d_bottom));
			filler(BOTTOM_LEFT, BoxFloat(x, y + fillHeight + d_top, d_left, d_bottom));

			filler(TOP, BoxFloat(x + d_left, y, fillWidth, d_top));
			filler(RIGHT, BoxFloat(x + fillWidth + d_left, y + d_top, d_right, fillHeight));
			filler(BOTTOM, BoxFloat(x + d_left, y + fillHeight + d_top, fillWidth, d_bottom));
			filler(LEFT, BoxFloat(x, y + d_top, d_left, fillHeight));

			filler(FILL, BoxFloat(x + d_left, y + d_top, fillWidth, fillHeight));
		}

		_A_ _M_ Image* d_image;
		_A_ _M_ string d_filetype;

		_A_ _M_ int d_top;
		_A_ _M_ int d_right;
		_A_ _M_ int d_bottom;
		_A_ _M_ int d_left;
		_A_ _M_ int d_margin;
		_A_ _M_ Dimension d_stretch;

		int d_width;
		int d_height;

		int d_solidWidth;
		int d_solidHeight;

		int d_fillWidth;
		int d_fillHeight;

		std::vector<Image> d_images;

		bool d_prepared;

		static Type& cls() { static Type ty; return ty; }
	};
}

#endif // TOY_IMAGESKIN_H
